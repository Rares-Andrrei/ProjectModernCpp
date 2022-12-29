#include "Map.h"

Map::Map(QWidget *parent)
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
void Map::onzona1Clicked()
{
	BattleWindow->show();
<<<<<<< Updated upstream
=======
	BattleWindow->show();
	Color::ColorEnum color = Color::getColor(1);
	std::string culoare = Color::ColorToString(color);
	QString qstr = QString::fromStdString(culoare);
	ui.zona1->setPalette(QPalette(QColor(qstr)));
	ui.zona1->setAutoFillBackground(true);
	update();
>>>>>>> Stashed changes
}
void Map::onzona2Clicked()
{
	BattleWindow->show();
}

void Map::onzona3Clicked()
{
	BattleWindow->show();
}

void Map::onzona4Clicked()
{
	BattleWindow->show();
}

void Map::onzona5Clicked()
{
	BattleWindow->show();
}

void Map::onzona6Clicked()
{
	BattleWindow->show();
}

void Map::onzona7Clicked()
{
	BattleWindow->show();
}

void Map::onzona8Clicked()
{
	BattleWindow->show();
}

void Map::onzona9Clicked()
{
	BattleWindow->show();
}
