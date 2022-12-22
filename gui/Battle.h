#pragma once

#include <QMainWindow>
#include "ui_Battle.h"

class Battle : public QMainWindow
{
	Q_OBJECT

public:
	Battle(QWidget *parent = nullptr);
	~Battle();

private:
	Ui::BattleClass ui;
};
