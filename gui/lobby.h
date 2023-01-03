#pragma once

#include <QMainWindow>
#include "ui_lobby.h"
#include "TriviadorGame.h"
#include "Route.h"
#include <qmessagebox.h>

#include "PlayersInstance.h"
#include <cpr/cpr.h>

#include <qtimer.h>
#include <qthread.h>

class lobby : public QMainWindow
{
	Q_OBJECT

public:
	lobby(Route& route, QWidget* parent = nullptr);
	void setPlayer(PlayerInstance player);
	~lobby();



private:
	PlayerInstance Player;
	bool m_stopLoop;
	Route& m_routes;
	Ui::lobbyClass ui;
	std::unique_ptr<TriviadorGame> Game;
private slots:
	void onTwoPlayersButtonClicked();
	void onThreePlayersButtonClicked();
	void onFourPlayersButtonClicked();

	void onCancelButtonClicked();
};
// broadcast