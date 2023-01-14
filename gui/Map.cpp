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
			Send_Response_To_Server(index);
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

	std::pair<int, Color::ColorEnum> colorZone = m_GameInstance->chooseRegion(ZoneId, m_player->getColor());
	disableAllButtons();
	m_gridButtons->setButtonColor(colorZone.first, colorZone.second);
	m_gridButtons->setCustomName(colorZone.first, "Zona " + QString::number(colorZone.first), 100, 0);
	// 100 trebuie modificat cu ce exista pe server ( ruta ), la fel si pentru 0

	QThread::msleep(10);

	emit emitMapUpdatedChooseRegionsPhase();

	this->hide();
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