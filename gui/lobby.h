#pragma once

#include <QMainWindow>
#include "ui_lobby.h"
#include "TriviadorGame.h"
#include "Route.h"
#include <qmessagebox.h>

#include "PlayersInstance.h"
#include <cpr/cpr.h>
#include <crow.h>
#include <qtimer.h>
#include <qthread.h>

class lobby : public QMainWindow
{
	Q_OBJECT

public:
	lobby(Route& route, QWidget* parent = nullptr);
	~lobby();



private:
	bool m_stopLoop;

	std::vector<Player> m_players;
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