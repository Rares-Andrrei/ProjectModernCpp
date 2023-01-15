#pragma once

#include <QMainWindow>
#include "ui_Podium.h"

class Podium : public QMainWindow
{
	Q_OBJECT

public:
	Podium(QWidget *parent = nullptr);
	~Podium();

private:
	Ui::PodiumClass ui;
};
