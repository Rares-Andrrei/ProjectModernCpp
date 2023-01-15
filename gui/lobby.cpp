#include "lobby.h"

void lobby::stylingTheLobby()
{
	ui.twoPlayersButton->setStyleSheet("QPushButton { background-image:url(:/gui/twoPlayers.png); text-align: left, up; border-radius: 5px; }");
	ui.threePlayersButton->setStyleSheet("QPushButton { background-image:url(:/gui/threePlayers.png); text-align: left, up; border-radius: 5px; }");
	ui.fourPlayersButton->setStyleSheet("QPushButton { background-image:url(:/gui/fourPlayers.png); text-align: left, up; border-radius: 5px; }");
	ui.loadingLabel->setMovie(m_waitingForPlayers.data());
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

lobby::lobby(const std::shared_ptr<Route>& route, QWidget* parent)
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
	m_routes->leaveLobby();
	if (m_routes->logOut())
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
	m_waitingForPlayers->start();
	m_routes->enterLobby(2, m_players);
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
		Game->setGameInstance(m_routes);
		Game->show();
		this->hide();
	}
}

void lobby::onThreePlayersButtonClicked()
{
	ui.lobbyGameModes->setCurrentIndex(1);
	m_waitingForPlayers->start();
	m_routes->enterLobby(3, m_players);
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
		Game->setNumberOfPlayers(3);
		Game->setPlayer(m_Player);
		Game->setPlayers(m_players);
		Game->setGameInstance(m_routes);
		Game->show();
		this->hide();
	}
}

void lobby::onFourPlayersButtonClicked()
{
	ui.lobbyGameModes->setCurrentIndex(1);
	m_waitingForPlayers->start();
	m_routes->enterLobby(4, m_players);
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
		Game->setNumberOfPlayers(4);
		Game->setPlayer(m_Player);
		Game->setPlayers(m_players);
		Game->setGameInstance(m_routes);
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
	if (m_routes->leaveLobby())
	{
		QMessageBox::information(this, "queue", "You left the game");
	}
	else
	{
		QMessageBox::information(this, "queue", "Error leaving the game");
	}
}

void lobby::on_gamesHistoryButton_clicked()
{
	ui.lobbyGameModes->setCurrentIndex(2);

	auto matchHistory = m_routes->getMatchHistoryRoute();

	ui.playerNameLabel->setText(m_PlayerName);
	ui.playerNameLabel->setText(ui.playerNameLabel->text() + " you played ");
	ui.playerNameLabel->setText(ui.playerNameLabel->text() + QString::number(matchHistory.size()));
	ui.playerNameLabel->setText(ui.playerNameLabel->text() + " games WOW");

	ui.tableMatchHistory->setRowCount(matchHistory.size());
	ui.tableMatchHistory->setColumnCount(6);
	ui.tableMatchHistory->setStyleSheet("background-color: rgb(229, 229, 229);");
	ui.tableMatchHistory->horizontalHeader()->setFixedHeight(50);
	ui.tableMatchHistory->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: rgb(120, 159, 110); }");
	ui.tableMatchHistory->verticalHeader()->setVisible(false);
	ui.tableMatchHistory->setToolTip("Sort the table by pressing the headers");

	ui.tableMatchHistory->setColumnWidth(0, 90);
	for (int i = 1; i < 6; i++)
		ui.tableMatchHistory->setColumnWidth(i, 81);

	QStringList headers = { "Date", "Player 1", "Player 2", "Player 3", "Player 4", "Place" };
	ui.tableMatchHistory->setHorizontalHeaderLabels(headers);

	int i = 0;
	std::string place;

	for (auto& m : matchHistory)
	{
		auto toAdd = m;
		for (int col = 0; col < 5; col++)
		{
			std::unique_ptr<QTableWidgetItem> item;
			if (QString(m[col].c_str()) == m_PlayerName)
			{
				place = std::to_string(col);
				item = std::make_unique<QTableWidgetItem>("you");
			}
			else
			{
				item = std::make_unique<QTableWidgetItem>(QString(toAdd[col].c_str()));
			}
			ui.tableMatchHistory->setItem(i, col, item.release());
		}
		std::unique_ptr<QTableWidgetItem> item = std::make_unique<QTableWidgetItem>(QString(place.c_str()));
		ui.tableMatchHistory->setItem(i, 5, item.release());
		i++;
	}
	ui.tableMatchHistory->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void lobby::on_backButton_clicked()
{
	ui.lobbyGameModes->setCurrentIndex(0);
}
