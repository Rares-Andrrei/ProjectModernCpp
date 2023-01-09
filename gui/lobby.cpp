#include "lobby.h"

void lobby::stylingTheLobby()
{
	ui.twoPlayersButton->setStyleSheet("QPushButton { background-image:url(:/gui/twoPlayers.png); text-align: left, up; border-radius: 5px; }");
	ui.threePlayersButton->setStyleSheet("QPushButton { background-image:url(:/gui/threePlayers.png); text-align: left, up; border-radius: 5px; }");
	ui.fourPlayersButton->setStyleSheet("QPushButton { background-image:url(:/gui/fourPlayers.png); text-align: left, up; border-radius: 5px; }");

	QMovie* movie = new QMovie(":/gui/32x32.gif");
	ui.loadingLabel->setMovie(movie);
	ui.loadingLabel->show();
	movie->start();
}

void lobby::buttonsConnections()
{
	connect(ui.twoPlayersButton, SIGNAL(clicked()), SLOT(onTwoPlayersButtonClicked()));
	connect(ui.threePlayersButton, SIGNAL(clicked()), SLOT(onThreePlayersButtonClicked()));
	connect(ui.fourPlayersButton, SIGNAL(clicked()), SLOT(onFourPlayersButtonClicked()));

	connect(ui.cancelButton, SIGNAL(clicked()), SLOT(onCancelButtonClicked()));
}

void lobby::catPictures()
{
	filenames.append(":/slideShowCats/cat1.png");
	filenames.append(":/slideShowCats/cat2.png");
	filenames.append(":/slideShowCats/cat3.png");
	filenames.append(":/slideShowCats/cat4.png");
	filenames.append(":/slideShowCats/cat5.png");
	filenames.append(":/slideShowCats/cat6.png");
	filenames.append(":/slideShowCats/cat7.png");
	filenames.append(":/slideShowCats/cat8.png");
	ui.catPicturesLabel->setPixmap(filenames.at(i));
}

void lobby::nextOrPrevious()
{
	int maxSize = filenames.size() - 1;
	if (i > maxSize) { i = 0; }
	if (i < 0) { i = maxSize; }

	if (i <= maxSize && i >= 0) {
		ui.catPicturesLabel->setPixmap(filenames.at(i));
	}
}


lobby::lobby(Route& route, QWidget* parent)
	: m_routes(route), QMainWindow(parent)
{
	ui.setupUi(this);

	stylingTheLobby();
	buttonsConnections();
	catPictures();
}

void lobby::on_nextButton_clicked()
{
	i++;
	nextOrPrevious();
}

void lobby::on_previousButton_clicked()
{
	i--;
	nextOrPrevious();
}

void lobby::setPlayer(const QString& playerName)
{
	this->m_PlayerName = playerName;
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

	for (auto& player : m_players)
	{
		if (player->getName() == m_PlayerName)
		{
			m_Player = player;
			break;
		}
	}

	if (m_players.size() > 0)
	{
		Game.reset(new TriviadorGame());
		Game->setNumberOfPlayers(2);
		Game->setPlayer(m_Player);
		Game->setPlayers(m_players);
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

