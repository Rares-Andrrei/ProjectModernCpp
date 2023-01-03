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
{}
void Map::setNumberOfInterractions(const int& numberOfInterractions)
{
	m_numberOfInterractions = numberOfInterractions;
}
void Map::setPlayer(const std::shared_ptr<PlayerInstance>& player)
{
	m_player = player;
}
void Map::onzona1Clicked()
{
	if (m_validateMove == true)
	{
		m_validateMove = false;
		m_numberOfInterractions--;
		ui.zona1->setAutoFillBackground(true);
		ui.zona1->setPalette(QPalette(QColor(QString::fromStdString(ColorToString(m_player->getColor())))));
	}
	else {
		QMessageBox::information(this, "Error", "You cann't move here");
	}
}
void Map::onzona2Clicked()
{
	if (m_validateMove == true)
	{
		m_validateMove = false;
		m_numberOfInterractions--;
		ui.zona2->setAutoFillBackground(true);
		ui.zona2->setPalette(QPalette(QColor(QString::fromStdString(ColorToString(m_player->getColor())))));
	}
	else {
		QMessageBox::information(this, "Error", "You cann't move here");
	}
}

void Map::onzona3Clicked()
{
	if (m_validateMove == true)
	{
		m_validateMove = false;
		m_numberOfInterractions--;
		ui.zona3->setAutoFillBackground(true);
		ui.zona3->setPalette(QPalette(QColor(QString::fromStdString(ColorToString(m_player->getColor())))));
	}
	else {
		QMessageBox::information(this, "Error", "You cann't move here");
	}
}

void Map::onzona4Clicked()
{
	if (m_validateMove == true)
	{
		m_validateMove = false;
		m_numberOfInterractions--;
		ui.zona4->setAutoFillBackground(true);
		ui.zona4->setPalette(QPalette(QColor(QString::fromStdString(ColorToString(m_player->getColor())))));
	}
	else {
		QMessageBox::information(this, "Error", "You cann't move here");
	}
}

void Map::onzona5Clicked()
{
	if (m_validateMove == true)
	{
		m_validateMove = false;
		m_numberOfInterractions--;
		ui.zona5->setAutoFillBackground(true);
		ui.zona5->setPalette(QPalette(QColor(QString::fromStdString(ColorToString(m_player->getColor())))));
	}
	else {
		QMessageBox::information(this, "Error", "You cann't move here");
	}
}

void Map::onzona6Clicked()
{
	if (m_validateMove == true)
	{
		m_validateMove = false;
		m_numberOfInterractions--;
		ui.zona6->setAutoFillBackground(true);
		ui.zona6->setPalette(QPalette(QColor(QString::fromStdString(ColorToString(m_player->getColor())))));
	}
	else {
		QMessageBox::information(this, "Error", "You cann't move here");
	}
}

void Map::onzona7Clicked()
{
	if (m_validateMove == true)
	{
		m_validateMove = false;
		m_numberOfInterractions--;
		ui.zona7->setAutoFillBackground(true);
		ui.zona7->setPalette(QPalette(QColor(QString::fromStdString(ColorToString(m_player->getColor())))));
	}
	else {
		QMessageBox::information(this, "Error", "You cann't move here");
	}
}

void Map::onzona8Clicked()
{
	if (m_validateMove == true)
	{
		m_validateMove = false;
		m_numberOfInterractions--;
		ui.zona8->setAutoFillBackground(true);
		ui.zona8->setPalette(QPalette(QColor(QString::fromStdString(ColorToString(m_player->getColor())))));
	}
	else {
		QMessageBox::information(this, "Error", "You cann't move here");
	}
}

void Map::onzona9Clicked()
{
	if (m_validateMove == true)
	{
		m_validateMove = false;
		m_numberOfInterractions--;
		ui.zona9->setAutoFillBackground(true);
		ui.zona9->setPalette(QPalette(QColor(QString::fromStdString(ColorToString(m_player->getColor())))));
	}
	else {
		QMessageBox::information(this, "Error", "You cann't move here");
	}
}

