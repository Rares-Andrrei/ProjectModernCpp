#pragma once

#include <QMainWindow>
#include "ui_TriviadorGame.h"

class TriviadorGame : public QMainWindow
{
	Q_OBJECT

public:
	TriviadorGame(QWidget *parent = nullptr);
	~TriviadorGame();

private:
	Ui::TriviadorGameClass ui;
};
