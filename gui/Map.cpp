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
	connect(ui.zona1, SIGNAL(clicked()), SLOT(onzona1Clicked()));
	connect(ui.zona2, SIGNAL(clicked()), SLOT(onzona2Clicked()));
	connect(ui.zona3, SIGNAL(clicked()), SLOT(onzona3Clicked()));
	connect(ui.zona4, SIGNAL(clicked()), SLOT(onzona4Clicked()));
	connect(ui.zona5, SIGNAL(clicked()), SLOT(onzona5Clicked()));
	connect(ui.zona6, SIGNAL(clicked()), SLOT(onzona6Clicked()));
	connect(ui.zona7, SIGNAL(clicked()), SLOT(onzona7Clicked()));
	connect(ui.zona8, SIGNAL(clicked()), SLOT(onzona8Clicked()));
	connect(ui.zona9, SIGNAL(clicked()), SLOT(onzona9Clicked()));
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
	// Trimite raspuns la server cu zona selectata
	if (this->isHidden())
		this->show();

	std::pair<int, Color::ColorEnum> colorZone = m_GameInstance->chooseRegion(ZoneId, m_player->getColor());
	//QThread::msleep(1000);
	disableAllButtons();
	QAbstractButton* button = nullptr;
	if (colorZone.first == 0)
		button = ui.zona1;
	else if (colorZone.first == 1)
		button = ui.zona2;
	else if (colorZone.first == 2)
		button = ui.zona3;
	else if (colorZone.first == 3)
		button = ui.zona4;
	else if (colorZone.first == 4)
		button = ui.zona5;
	else if (colorZone.first == 5)
		button = ui.zona6;
	else if (colorZone.first == 6)
		button = ui.zona7;
	else if (colorZone.first == 7)
		button = ui.zona8;
	else if (colorZone.first == 8)
		button = ui.zona9;
	updateAZone(button, colorZone.second);
	/*switch (colorZone.first)
	{
	default:
		QThread::msleep(500);
	case 1:
	{
		ui.zona1->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(colorZone.second));
		ui.zona1->setPalette(pal);
		break;
	}
	case 2:
	{
		ui.zona2->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(colorZone.second));
		ui.zona2->setPalette(pal);
		break;
	}
	case 3:
	{
		ui.zona3->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(colorZone.second));
		ui.zona3->setPalette(pal);
		break;
	}
	case 4:
	{
		ui.zona4->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(colorZone.second));
		ui.zona4->setPalette(pal);
		break;
	}
	case 5:
	{
		ui.zona5->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(colorZone.second));
		ui.zona5->setPalette(pal);
		break;
	}
	case 6:
	{
		ui.zona6->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(colorZone.second));
		ui.zona6->setPalette(pal);
		break;
	}
	case 7:
	{
		ui.zona7->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(colorZone.second));
		ui.zona7->setPalette(pal);
		break;
	}
	case 8:
	{
		ui.zona8->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(colorZone.second));
		ui.zona8->setPalette(pal);
		break;
	}
	case 9:
	{
		ui.zona9->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(colorZone.second));
		ui.zona9->setPalette(pal);
		break;
	}
	}*/
	QThread::msleep(100);

	emit emitMapUpdatedChooseRegionsPhase();

	this->hide();
}
void emitMapUpdatedChooseRegionsPhase()
{

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

void Map::updateAZone(QAbstractButton* button, const Color::ColorEnum& color)
{
	button->setAutoFillBackground(true);
	QPalette pal = QPalette(getColor(color));
	button->setPalette(pal);
}

void Map::onzona1Clicked()
{
	int ZoneId = 0;
	if (m_gamePhase == GamePhase::ChooseBase)
	{
		if (m_board->AddZoneAsBase(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona1, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
	else if (m_gamePhase == GamePhase::ChooseRegions)
	{
		if (m_board->AddCloseZone(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona1, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
}

void Map::playersAvatar()
{
	//ui.player1Avatar->setStyleSheet();
	ui.player1Name->setText(m_players[0]->getName());
	ui.player2Name->setText(m_players[1]->getName());
}


void Map::onzona2Clicked()
{
	int ZoneId = 1;
	if (m_gamePhase == GamePhase::ChooseBase)
	{
		if (m_board->AddZoneAsBase(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona2, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
	else if (m_gamePhase == GamePhase::ChooseRegions)
	{
		if (m_board->AddCloseZone(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona2, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
}

void Map::onzona3Clicked()
{
	int ZoneId = 2;
	if (m_gamePhase == GamePhase::ChooseBase)
	{
		if (m_board->AddZoneAsBase(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona3, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
	else if (m_gamePhase == GamePhase::ChooseRegions)
	{
		if (m_board->AddCloseZone(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona3, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
}

void Map::onzona4Clicked()
{
	int ZoneId = 3;
	if (m_gamePhase == GamePhase::ChooseBase)
	{
		if (m_board->AddZoneAsBase(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona4, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
	else if (m_gamePhase == GamePhase::ChooseRegions)
	{
		if (m_board->AddCloseZone(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona4, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
}

void Map::onzona5Clicked()
{
	int ZoneId = 4;
	if (m_gamePhase == GamePhase::ChooseBase)
	{
		if (m_board->AddZoneAsBase(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona5, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
	else if (m_gamePhase == GamePhase::ChooseRegions)
	{
		if (m_board->AddCloseZone(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona5, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
}

void Map::onzona6Clicked()
{
	int ZoneId = 5;
	if (m_gamePhase == GamePhase::ChooseBase)
	{
		if (m_board->AddZoneAsBase(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona6, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
	else if (m_gamePhase == GamePhase::ChooseRegions)
	{
		if (m_board->AddCloseZone(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona6, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
}

void Map::onzona7Clicked()
{
	int ZoneId = 6;
	if (m_gamePhase == GamePhase::ChooseBase)
	{
		if (m_board->AddZoneAsBase(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona7, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
	else if (m_gamePhase == GamePhase::ChooseRegions)
	{
		if (m_board->AddCloseZone(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona7, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
}

void Map::onzona8Clicked()
{
	int ZoneId = 7;
	if (m_gamePhase == GamePhase::ChooseBase)
	{
		if (m_board->AddZoneAsBase(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona8, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
	else if (m_gamePhase == GamePhase::ChooseRegions)
	{
		if (m_board->AddCloseZone(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona8, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
}

void Map::onzona9Clicked()
{
	int ZoneId = 8;
	if (m_gamePhase == GamePhase::ChooseBase)
	{
		if (m_board->AddZoneAsBase(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona9, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
	else if (m_gamePhase == GamePhase::ChooseRegions)
	{
		if (m_board->AddCloseZone(ZoneId, m_player->getColor()))
		{
			updateAZone(ui.zona9, m_player->getColor());
			Send_Response_To_Server(ZoneId);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
}

