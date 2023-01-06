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

void lobby::setPlayer(const std::shared_ptr<PlayerQString>& play)
{
	auto val = play->getName();
	this->m_Player = std::make_shared<PlayerQString>(val);
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
	m_routes.enterLobby(2, m_players);
	if (m_players.size() > 0)
	{
		Game.reset(new TriviadorGame());
		Game->setNumberOfPlayers(2);
		Game->setPlayer(m_Player);
		Game->show();
		this->hide();
	}
}

void lobby::onThreePlayersButtonClicked()
{
	ui.lobbyGameModes->setCurrentIndex(1);
	m_routes.enterLobby(3, m_players);
	if (m_players.size() > 0)
	{
		Game.reset(new TriviadorGame());
		Game->setNumberOfPlayers(3);
		Game->show();
		this->hide();
	}
}

void lobby::onFourPlayersButtonClicked()
{
	ui.lobbyGameModes->setCurrentIndex(1);
	m_routes.enterLobby(4, m_players);
	if (m_players.size() > 0)
	{
		Game.reset(new TriviadorGame());
		Game->setNumberOfPlayers(4);
		Game->show();
		this->hide();
	}

}

void lobby::onCancelButtonClicked()
{
	ui.lobbyGameModes->setCurrentIndex(0);
	QPushButton* button = ui.twoPlayersButton;
	button->setEnabled(true);
	button->show();
	if (m_routes.leaveLobby())
	{
		QMessageBox::information(this, "queue", "You left the queue");
	}
	else
	{
		QMessageBox::information(this, "queue", "Error leaving the queue");
	}
}
