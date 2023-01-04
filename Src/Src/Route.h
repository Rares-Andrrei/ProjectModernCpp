#pragma once
#include "GameLogic.h"
#include "CredentialErrors.h"
#include "Database.h"
#include <crow.h>
#include "Players.h"

class Route
{
	Database& m_db;
	crow::SimpleApp m_app;
	std::shared_ptr<Players> m_players;

	std::unordered_map<uint16_t, GameLogic> gamesActive;
	std::unordered_set< std::string> playersInGame;
	std::list<std::shared_ptr<Player>> twoPlayers;

public:
	Route(Database& db, std::shared_ptr<Players> players);
	void loginRoute();
	void enterTwoPlayersLobby();
	void exitTwoPlayersLobby();
	void signUpRoute();
	void logOutRoute();
	void startApp();
}; 