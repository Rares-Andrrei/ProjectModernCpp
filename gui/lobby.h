#pragma once

#include <QMainWindow>
#include "ui_lobby.h"

class lobby : public QMainWindow
{
	Q_OBJECT

public:
	lobby(QWidget *parent = nullptr);
	~lobby();

private:
	Ui::lobbyClass ui;
};
