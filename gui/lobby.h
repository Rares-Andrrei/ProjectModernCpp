#pragma once

#include <QMainWindow>
#include "ui_lobby.h"
#include "TriviadorGame.h"
#include "Route.h"
#include <qmessagebox.h>
#include <cpr/cpr.h>
#include <crow.h>
#include "CredentialErrors.h"
#include <string>
#include "PlayerQString.h"
#include <cpr/cpr.h>
#include <memory>
#include <crow.h>
#include <qtimer.h>
#include <qthread.h>

class lobby : public QMainWindow
{
	Q_OBJECT

public:
	lobby(Route& route, QWidget* parent = nullptr);
	void setPlayer(const std::shared_ptr<PlayerQString>& player);
	~lobby();



private:
	std::shared_ptr<PlayerQString> m_Player;
	bool m_stopLoop;

	std::vector<PlayerQString> m_players;
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