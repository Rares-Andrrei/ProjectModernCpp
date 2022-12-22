#include "Map.h"

Map::Map(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	battleWindow.reset(new Battle());
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
