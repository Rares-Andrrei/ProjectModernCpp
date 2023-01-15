#include "Map.h"

Map::Map(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowState(Qt::WindowFullScreen);

	BattleWindow.reset(new Battle());
	for (const auto& button : findChildren<QAbstractButton*>())
	{
		button->setStyleSheet("background:transparent;"
			"border:1px solid black;"
			"border-radius: 15px;");
	}
}

Map::~Map()
{

}

void Map::setPlayer(const std::shared_ptr<PlayerQString>& player)
{
	m_player = player;
}

void Map::setPlayers(const std::vector<std::shared_ptr<PlayerQString>>& players)
{
	m_players = players;
	if (players.size() == 2)
	{
		m_gridButtons = new  GridButtons(3, 3, this);
	}
	else if (players.size() == 3)
	{
		m_gridButtons = new  GridButtons(3, 5, this);
	}
	else
	{
		m_gridButtons = new  GridButtons(4, 6, this);
	}
	setupGridButtons();
}

void Map::onButtonClickedSignal(int index)
{
	if (m_gamePhase == GamePhase::ChooseBase)
	{
		if (m_GameInstance->checkValidBasePosition(index))
			Send_Response_To_Server(index);
		else
			QMessageBox::warning(this, "Error", "Invalid Base Position");
	}
	else if (m_gamePhase == GamePhase::ChooseRegions)
	{
		if (m_GameInstance->checkValidRegionPosition(index, m_player->getColor()))
			Send_Response_To_Server(index);
		else
			QMessageBox::warning(this, "Error", "Invalid Region Position");
	}
	else if (m_gamePhase == GamePhase::Duels)
	{
		if (m_GameInstance->checkValidAttackMove(index, m_player->getColor()))
			send_Attacker_Response_To_Server(index);
		else
			QMessageBox::warning(this, "Error", "Invalid Attack Position");
	}
}


void Map::setGameInstance(const std::shared_ptr<Route>& GameInstance)
{
	m_GameInstance = GameInstance;
}

void Map::setPhase(GamePhase gamePhase)
{
	m_gamePhase = gamePhase;
}

QColor Map::getColor(const Color::ColorEnum& color)
{
	switch (color)
	{
	case Color::ColorEnum::None:
		return QColorConstants::Black;
		break;
	case Color::ColorEnum::Red:
		return QColorConstants::Red;
		break;
	case Color::ColorEnum::Green:
		return QColorConstants::Green;
		break;
	case Color::ColorEnum::Blue:
		return QColorConstants::Blue;
		break;
	case Color::ColorEnum::Yellow:
		return QColorConstants::Yellow;
		break;
	default:
		return QColorConstants::White;
		break;
	}
}

void Map::Send_Response_To_Server(int ZoneId)
{
	if (this->isHidden())
		this->show();
	updatePlayersInfo();

	std::pair<int, Color::ColorEnum> colorZone = m_GameInstance->chooseRegion(ZoneId, m_player->getColor());
	disableAllButtons();
	m_gridButtons->setButtonColor(colorZone.first, colorZone.second);
	QThread::msleep(QRandomGenerator::global()->bounded(1, 10));
	auto zoneInfo = m_GameInstance->updateZoneInfo(colorZone.first);
	auto& [zoneId, zoneColor, zoneScore, zoneLifes] = zoneInfo;

	if (zoneColor != Color::ColorEnum::None)
	{
		m_gridButtons->setButtonColor(zoneId, zoneColor);
		m_gridButtons->setCustomName(zoneId, "Zona " + QString::number(zoneId), zoneScore, zoneLifes);
	}

	QThread::msleep(10);

	this->hide();
	emit emitMapUpdatedChooseRegionsPhase();
}

void Map::send_Attacker_Response_To_Server(int ZoneId)
{
	if (this->isHidden())
		this->show();
	QThread::msleep(QRandomGenerator::global()->bounded(1, 50));
	std::tuple<Color::ColorEnum, Color::ColorEnum, int> colors = m_GameInstance->getDuelingPlayersAndZone(m_player->getColor(), ZoneId);
	updatePlayersInfo();

	//m_gridButtons->setButtonColor(std::get<2>(colors), Color::ColorEnum::None);

	disableAllButtons();
	QThread::msleep(QRandomGenerator::global()->bounded(1, 50));

	this->hide();

	emit emitDuelParticipants({ std::get<0>(colors),std::get<1>(colors) });
}

void Map::getUpdatedZones(const std::vector<std::tuple<int, Color::ColorEnum, int, int>>& UpdatedZones)
{
	for (const auto& zone : UpdatedZones)
	{
		auto& [index, color, score, nrOfLives] = zone;
		m_gridButtons->setButtonColor(index, color);
		m_gridButtons->setCustomName(index, "Zona " + QString::number(index), score, nrOfLives);
	}
}
void Map::getUpdatedZones(const std::vector<std::tuple<int, Color::ColorEnum, int>>& UpdatedZones)
{
	for (const auto& zone : UpdatedZones)
	{
		auto& [index, color, score] = zone;
		m_gridButtons->setButtonColor(index, color);
		m_gridButtons->setCustomName(index, "Zona " + QString::number(index), score);
	}
	emit emitGetNextDuel();
}


void Map::disableAllButtons()
{
	for (const auto& button : findChildren<QAbstractButton*>())
	{
		button->setEnabled(false);
	}
}

void Map::enableAllButtons()
{
	for (const auto& button : findChildren<QAbstractButton*>())
	{
		button->setEnabled(true);
	}
	playersAvatar();
}

void Map::updatePlayersInfo()
{
	auto playerInfo = m_GameInstance->updatePlayersInfo();
	for (auto& player : m_players)
	{
		for (auto& info : playerInfo)
		{
			if (player->getColor() == info.first)
			{
				player->setScore(info.second);
			}
		}
	}

	for (int i = 0; i < m_players.size(); i++)
	{
		if (m_players[i]->getName() == m_player->getName())
		{
			ui.player1Score->setText(QString::number(m_player->getScore()));
		}
		else if (i == 1)
		{
			ui.player2Score->setText(QString::number(m_players[i]->getScore()));
		}
		else if (i == 2)
		{
			ui.player3Score->setText(QString::number(m_players[i]->getScore()));
		}
		else
			ui.player4Score->setText(QString::number(m_players[i]->getScore()));

	}

}

void Map::playersAvatar()
{
	QStringList filenames;
	filenames.append(":/gui/red.png");
	filenames.append(":/gui/blue.png");
	filenames.append(":/gui/yellow.png");
	filenames.append(":/gui/green.png");
	for (int i = 0; i < m_players.size(); i++)
	{
		auto playerColor = m_players[i]->getColor();

		if (m_players[i]->getName() == m_player->getName())
		{
			if (playerColor == Color::ColorEnum::Red)
				ui.player1Avatar->setPixmap(filenames.at(0));
			else if (playerColor == Color::ColorEnum::Blue)
				ui.player1Avatar->setPixmap(filenames.at(1));
			else if (playerColor == Color::ColorEnum::Yellow)
				ui.player1Avatar->setPixmap(filenames.at(2));
			else if (playerColor == Color::ColorEnum::Green)
				ui.player1Avatar->setPixmap(filenames.at(3));
			ui.player1Name->setText("you");
		}
		else
		{
			if (i == 1)
			{
				if (playerColor == Color::ColorEnum::Red)
					ui.player2Avatar->setPixmap(filenames.at(0));
				else if (playerColor == Color::ColorEnum::Blue)
					ui.player2Avatar->setPixmap(filenames.at(1));
				else if (playerColor == Color::ColorEnum::Yellow)
					ui.player2Avatar->setPixmap(filenames.at(2));
				else if (playerColor == Color::ColorEnum::Green)
					ui.player2Avatar->setPixmap(filenames.at(3));

				ui.player2Name->setText(m_players[i]->getName());
			}
			else if (i == 2)
			{
				if (playerColor == Color::ColorEnum::Red)
					ui.player3Avatar->setPixmap(filenames.at(0));
				else if (playerColor == Color::ColorEnum::Blue)
					ui.player3Avatar->setPixmap(filenames.at(1));
				else if (playerColor == Color::ColorEnum::Yellow)
					ui.player3Avatar->setPixmap(filenames.at(2));
				else if (playerColor == Color::ColorEnum::Green)
					ui.player3Avatar->setPixmap(filenames.at(3));

				ui.player3Name->setText(m_players[i]->getName());
			}
			else
			{
				if (playerColor == Color::ColorEnum::Red)
					ui.player4Avatar->setPixmap(filenames.at(0));
				else if (playerColor == Color::ColorEnum::Blue)
					ui.player4Avatar->setPixmap(filenames.at(1));
				else if (playerColor == Color::ColorEnum::Yellow)
					ui.player4Avatar->setPixmap(filenames.at(2));
				else if (playerColor == Color::ColorEnum::Green)
					ui.player4Avatar->setPixmap(filenames.at(3));

				ui.player4Name->setText(m_players[i]->getName());
			}
		}
	}
	updatePlayersInfo();

}

void Map::setupGridButtons()
{
	m_gridButtons->setSizeAndAlignment(70, 70);
	layout = std::make_shared<QVBoxLayout>();
	layout->addWidget(m_gridButtons);
	layout->setAlignment(Qt::AlignCenter);
	ui.centralWidget->setLayout(layout.get());
	m_gridButtons->show();
	connect(m_gridButtons, &GridButtons::sendButtonIndexClicked, this, &Map::onButtonClickedSignal);
}