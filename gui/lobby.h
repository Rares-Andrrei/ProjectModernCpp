#pragma once

#include <QMainWindow>
#include "ui_lobby.h"
#include"Map.h"
class lobby : public QMainWindow
{
	Q_OBJECT

public:
	lobby(QWidget *parent = nullptr);
	~lobby();

private:
	Ui::lobbyClass ui;
	std::shared_ptr<Map>MapWindow;
private slots:
	void ontwoPlayersButtonClicked();
};
