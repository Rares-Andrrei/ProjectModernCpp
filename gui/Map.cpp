#include "Map.h"

Map::Map(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	BattleWindow.reset(new Battle());
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

void Map::setNumberOfInterractions(int numberOfInterractions)
{
	m_numberOfInterractions = numberOfInterractions;
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

	switch (colorZone.first)
	{
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
	default:
		break;
	}
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

void Map::onzona1Clicked()
{
	if (m_validateMove == true)
	{
		m_validateMove = true;
		m_numberOfInterractions--;
		ui.zona1->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(m_player->getColor()));
		ui.zona1->setPalette(pal);
		Send_Response_To_Server(1);
	}
	else {
		QMessageBox::information(this, "Error", "You can't move here");
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
	if (m_validateMove == true)
	{
		m_validateMove = true;
		m_numberOfInterractions--;
		ui.zona2->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(m_player->getColor()));
		ui.zona2->setPalette(pal);
		Send_Response_To_Server(2);
	}
	else {
		QMessageBox::information(this, "Error", "You can't move here");
	}
}

void Map::onzona3Clicked()
{
	if (m_validateMove == true)
	{
		m_validateMove = true;
		m_numberOfInterractions--;
		ui.zona3->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(m_player->getColor()));
		ui.zona3->setPalette(pal);
		Send_Response_To_Server(3);
	}
	else {
		QMessageBox::information(this, "Error", "You can't move here");
	}
}

void Map::onzona4Clicked()
{
	if (m_validateMove == true)
	{
		m_validateMove = true;
		m_numberOfInterractions--;
		ui.zona4->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(m_player->getColor()));
		ui.zona4->setPalette(pal);
		Send_Response_To_Server(4);
	}
	else {
		QMessageBox::information(this, "Error", "You can't move here");
	}
}

void Map::onzona5Clicked()
{
	if (m_validateMove == true)
	{
		m_validateMove = true;
		m_numberOfInterractions--;
		ui.zona5->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(m_player->getColor()));
		ui.zona5->setPalette(pal);
		Send_Response_To_Server(5);
	}
	else {
		QMessageBox::information(this, "Error", "You can't move here");
	}
}

void Map::onzona6Clicked()
{
	if (m_validateMove == true)
	{
		m_validateMove = true;
		m_numberOfInterractions--;
		ui.zona6->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(m_player->getColor()));
		ui.zona6->setPalette(pal);
		Send_Response_To_Server(6);
	}
	else {
		QMessageBox::information(this, "Error", "You can't move here");
	}
}

void Map::onzona7Clicked()
{
	if (m_validateMove == true)
	{
		m_validateMove = true;
		m_numberOfInterractions--;
		ui.zona7->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(m_player->getColor()));
		ui.zona7->setPalette(pal);
		Send_Response_To_Server(7);
	}
	else {
		QMessageBox::information(this, "Error", "You can't move here");
	}
}

void Map::onzona8Clicked()
{
	if (m_validateMove == true)
	{
		m_validateMove = true;
		m_numberOfInterractions--;
		ui.zona8->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(m_player->getColor()));
		ui.zona8->setPalette(pal);
		Send_Response_To_Server(8);
	}
	else {
		QMessageBox::information(this, "Error", "You can't move here");
	}
}

void Map::onzona9Clicked()
{
	if (m_validateMove == true)
	{
		m_validateMove = true;
		m_numberOfInterractions--;
		ui.zona9->setAutoFillBackground(true);
		QPalette pal = QPalette(getColor(m_player->getColor()));
		ui.zona9->setPalette(pal);
		Send_Response_To_Server(9);
	}
	else {
		QMessageBox::information(this, "Error", "You can't move here");
	}
}

