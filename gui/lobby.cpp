#include "lobby.h"
#include <QMovie>

lobby::lobby(Route& route, QWidget* parent)
	: m_routes(route), QMainWindow(parent)
{
	ui.setupUi(this);

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

void lobby::setPlayer(const std::shared_ptr<Player>& play)
{
	this->m_Player = play;
}

lobby::~lobby()
{
	m_routes.leaveLobby();
	if (m_routes.logOut())
	{
		QMessageBox::information(this, "Logout", "U have been logged out");
		QApplication::closeAllWindows();
	}
	else {
		QMessageBox::information(this, "Failure", "The logout failed");
	}
}
void lobby::onTwoPlayersButtonClicked()
{
	ui.lobbyGameModes->setCurrentIndex(1);
	QTimer timer;
	m_stopLoop = false;
	QPushButton* button = ui.twoPlayersButton;
	button->setEnabled(false);

	QObject::connect(&timer, &QTimer::timeout, [&]()
		{
			int resp = m_routes.enterTwoPlayersLobby();

	if (resp == 201)
	{
		this->hide();
		//Queue message 
		//temporarly for testing 
		m_stopLoop = true;
		Game.reset(new TriviadorGame(this));
		Game->setNumberOfPlayers(2);
		Game->setPlayer(m_Player);
		Game->StartGame();
	}
	else if (resp == 200)
	{
		// Game found message
		m_stopLoop = true;
		Game->setNumberOfPlayers(2);
		Game->show();
		this->hide();
	}
	else
	{
		QMessageBox::information(this, "queue", "The queue failed");
		m_stopLoop = true;
	}
		});

	timer.start(3000);

	while (!m_stopLoop)
	{
		QCoreApplication::processEvents();
		QThread::msleep(100);
	}
	QThread::msleep(100);
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
	QPushButton* button = ui.twoPlayersButton;
	button->setEnabled(true);
	button->show();
	m_stopLoop = true;
	if (m_routes.leaveLobby())
	{
		QMessageBox::information(this, "queue", "You left the queue");
	}
	else
	{
		QMessageBox::information(this, "queue", "Error leaving the queue");
	}
}
