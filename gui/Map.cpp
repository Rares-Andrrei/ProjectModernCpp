#include "Map.h"

Map::Map(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
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
			// request to server :: cei doi participanti , in functie de jucatorul care ataca si zona selectata
			// response :: 2 culori 
			send_Attacker_Response_To_Server(index);
		else
			QMessageBox::warning(this, "Error", "Invalid Attack Position");
	}
}


void Map::setGameInstance(const std::shared_ptr<Route>& GameInstance)
{
	m_GameInstance = GameInstance;
}

void Map::setBoard(const std::shared_ptr<BoardInterpretation>& board)
{
	m_board = board;
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
		m_gridButtons->setCustomName(zoneId, "Zona " + QString::number(zoneId) , zoneScore , zoneLifes);
	}

	QThread::msleep(10);

	emit emitMapUpdatedChooseRegionsPhase();

	this->hide();
}

void Map::send_Attacker_Response_To_Server(int ZoneId)
{
	if (this->isHidden())
		this->show();
	updatePlayersInfo();
	
	std::pair<Color::ColorEnum, Color::ColorEnum> colors = { Color::ColorEnum::Red, Color::ColorEnum::Yellow };// varianta de test
	//Ruta prin care se trimite jucatorul si ZoneId , daca ZoneId e valid  , el e atacatorul

	disableAllButtons();
	QThread::msleep(QRandomGenerator::global()->bounded(1, 10));

	emit emitDuelParticipants(colors);

	this->hide();
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
}

void Map::playersAvatar()
{
	//ui.player1Avatar->setStyleSheet();
	ui.player1Name->setText(m_players[0]->getName());
	ui.player2Name->setText(m_players[1]->getName());
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