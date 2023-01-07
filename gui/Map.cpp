#include "Map.h"

Map::Map(QWidget* parent)
	: QMainWindow(parent)
{
	t_checkFinishState = std::make_unique<QTimer>();
	t_checkFinishState->setInterval(500);

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

	connect(t_checkFinishState.get(), SIGNAL(timeout()), SLOT(on_CheckFinishState_Timeout()));
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

void Map::showEvent(QShowEvent* event)
{
	t_checkFinishState->start();
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
	}
	else {
		QMessageBox::information(this, "Error", "You can't move here");
	}
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
	}
	else {
		QMessageBox::information(this, "Error", "You can't move here");
	}
}

void Map::on_CheckFinishState_Timeout()
{
	if (m_numberOfInterractions == 0)// sau  server ul zice ca tabla e plina)
	{
		t_checkFinishState->stop();
		this->hide();
		//emit signal  sa se stie sa se treaca la urmatoarea faza 
	}
}

