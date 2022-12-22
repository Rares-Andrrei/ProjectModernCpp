#pragma once

#include <QMainWindow>
#include "ui_Map.h"
#include"Battle.h"
class Map : public QMainWindow
{
	Q_OBJECT

public:
	Map(QWidget *parent = nullptr);
	~Map();

private:
	Ui::MapClass ui;
	std::shared_ptr<Battle>battleWindow;
private slots:
};
