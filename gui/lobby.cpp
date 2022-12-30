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

void lobby::setPlayer(Player play)
{
	this->player = play;
}

lobby::~lobby()
{
	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/logout" },
		cpr::Payload{
			{ "username", player.getFirstName()},
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
	QPushButton* button = ui.twoPlayersButton;
	button->setEnabled(false);

	QObject::connect(&timer, &QTimer::timeout, [&]()
		{

			auto response = cpr::Put(
				cpr::Url{ "http://localhost:18080/queueTwoPlayerGame" },
				cpr::Payload{
					{ "username", player.getFirstName()}
				});

	if (response.status_code == 201)
	{
		//Queue message 
	}
	else if (response.status_code == 200)
	{
		// Game found message
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
			{ "username", player.getFirstName()}
		});
	button->setEnabled(true);
	button->show();
	if (response.status_code != 200)
	{
		QMessageBox::information(this, "queue", "The queue failed");
	}
}
