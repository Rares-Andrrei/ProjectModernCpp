#include "lobby.h"
#include <QMovie>

lobby::lobby(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Game.reset(new TriviadorGame(this));

	ui.twoPlayersButton->setStyleSheet("QPushButton { background-image:url(:/gui/twoPlayers.png); text-align: left, up; border-radius: 5px; }");
	ui.threePlayersButton->setStyleSheet("QPushButton { background-image:url(:/gui/threePlayers.png); text-align: left, up; border-radius: 5px; }");
	ui.fourPlayersButton->setStyleSheet("QPushButton { background-image:url(:/gui/fourPlayers.png); text-align: left, up; border-radius: 5px; }");

	QMovie* movie = new QMovie(":/gui/32x32.gif");
	ui.loadingLabel->setMovie(movie);
	ui.loadingLabel->show();
	movie->start();

	connect(ui.twoPlayersButton, SIGNAL(clicked()), SLOT(onTwoPlayersButtonClicked()));
	connect(ui.threePlayersButton, SIGNAL(clicked()), SLOT(onThreePlayersButtonClicked()));
	connect(ui.fourPlayersButton, SIGNAL(clicked()), SLOT(onFourPlayersButtonClicked()));

	connect(ui.cancelButton, SIGNAL(clicked()), SLOT(onCancelButtonClicked()));
}

void lobby::setPlayer(PlayerInstance player)
{
	this->Player = player;
}

void lobby::onTwoPlayersButtonClicked()
{
	ui.lobbyGameModes->setCurrentIndex(1);

	QTimer timer;

	bool stopLoop = false;
	QPushButton* button = ui.twoPlayersButton;
	button->setEnabled(false);

	QObject::connect(&timer, &QTimer::timeout, [&]()
		{
			// TD : de mutat ruta intr-o functei separata 
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
		// Game found message
		stopLoop = true;
		Game->setNumberOfPlayers(2);
		Game->show();
		this->hide();
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
	button->setEnabled(true);
	button->show();
	if (response.status_code != 200)
	{
		QMessageBox::information(this, "queue", "The queue failed");
	}
}

void lobby::onThreePlayersButtonClicked()
{
	ui.lobbyGameModes->setCurrentIndex(1);

}

void lobby::onFourPlayersButtonClicked()
{
	ui.lobbyGameModes->setCurrentIndex(1);

}

void lobby::onCancelButtonClicked()
{
	ui.lobbyGameModes->setCurrentIndex(0);
}

lobby::~lobby()
{
	// TD : de mutat intr-o functie separata
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
