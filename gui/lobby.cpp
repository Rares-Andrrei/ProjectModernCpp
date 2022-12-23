#include "lobby.h"

lobby::lobby(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	MapWindow.reset(new Map());
	ui.twoPlayersButton->setStyleSheet("Text-align:left, up");
	ui.threePlayersButton->setStyleSheet("Text-align:left, up");
	ui.fourPlayersButton->setStyleSheet("Text-align:left, up");
	connect(ui.twoPlayersButton, SIGNAL(clicked()), SLOT(ontwoPlayersButtonClicked()));
}

void lobby::setPlayer(PlayerInstance player)
{
	this->Player = player;
}

lobby::~lobby()
{
	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/logout" },
		cpr::Payload{
			{ "username", Player.getFirstName()},
		}
	);

	if (response.status_code == 200 || response.status_code == 202) {
		QMessageBox::information(this, "Logout", "U have been logged out");


		QApplication::closeAllWindows();
	}
	else {
		QMessageBox::information(this, "Failure", "The logout failed");
	}
}
void lobby::ontwoPlayersButtonClicked()
{
	QTimer timer;

	bool stopLoop = false;
	QObject::connect(&timer, &QTimer::timeout, [&]()
		{

			auto response = cpr::Put(
				cpr::Url{ "http://localhost:18080/queueTwoPlayerGame" },
				cpr::Payload{
					{ "username", Player.getFirstName()}
				});

	if (response.status_code == 201)
	{
		//Queue message 
	}
	else if (response.status_code == 200)
	{
		QMessageBox::information(this, "queue", "Game started");
		stopLoop = true;
		MapWindow->show();
		this->close();
	}
	else
	{
		QMessageBox::information(this, "queue", "The queue failed");
		stopLoop = true;
	}
		});

	timer.start(3000);

	while (!stopLoop)
	{
		QCoreApplication::processEvents();
		QThread::msleep(100);
	}
	QThread::msleep(5000);
	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/eliminatePlayerFromQueue" },
		cpr::Payload{
			{ "username", Player.getFirstName()}
		});
	if (response.status_code != 200)
	{
		QMessageBox::information(this, "queue", "The queue failed");
	}
}
