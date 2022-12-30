#pragma once

#include <QMainWindow>
#include "ui_Map.h"
#include"Battle.h"

#include "../Player/Player/Player.h"

class Map : public QMainWindow
{
	Q_OBJECT

public:
	Map(QWidget *parent = nullptr);
	~Map();

	//void 
private:
	Player player;
	Ui::MapClass ui;
	std::shared_ptr<Battle>BattleWindow;
private slots:
	void onzona1Clicked();
	void onzona2Clicked();
	void onzona3Clicked();
	void onzona4Clicked();
	void onzona5Clicked();
	void onzona6Clicked();
	void onzona7Clicked();
	void onzona8Clicked();
	void onzona9Clicked();
};
