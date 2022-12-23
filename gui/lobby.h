#pragma once

#include <QMainWindow>
#include "ui_lobby.h"
#include"Map.h"
#include <qmessagebox.h>

#include "PlayersInstance.h"
#include <cpr/cpr.h>

#include <qtimer.h>
#include <qthread.h>

class lobby : public QMainWindow
{
	Q_OBJECT

public:
	lobby(QWidget *parent = nullptr);
	void setPlayer(PlayerInstance player);
	~lobby();

	
private:
	PlayerInstance Player;
	
	Ui::lobbyClass ui;
	std::shared_ptr<Map>MapWindow;
private slots:
	void ontwoPlayersButtonClicked();
};
// broadcast