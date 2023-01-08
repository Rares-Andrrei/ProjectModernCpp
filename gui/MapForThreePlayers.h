#pragma once

#include <QMainWindow>
#include "ui_MapForThreePlayers.h"

class MapForThreePlayers : public QMainWindow
{
	Q_OBJECT

public:
	MapForThreePlayers(QWidget *parent = nullptr);
	~MapForThreePlayers();

private:
	Ui::MapForThreePlayersClass ui;
};
