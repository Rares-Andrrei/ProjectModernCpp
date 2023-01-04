#pragma once
#include "GameLogic.h"
#include "CredentialErrors.h"
#include "QTypeNumerical.h"
#include "Database.h"
#include <crow.h>
#include "PlayersQueue.h"

class Route
{
	Database& m_db;
	crow::SimpleApp m_app;
	std::shared_ptr<PlayersQueue> m_waitingList;


	std::unordered_map<uint16_t, GameLogic> gamesActive;
	std::unordered_set< std::string> playersInGame;
	std::list<std::shared_ptr<Player>> twoPlayers;

public:
	Route(Database& db, std::shared_ptr<PlayersQueue> players);

//	void getQuestionTypeNumericalRoute();


	void loginRoute();

	void enterLobbyRoute();
	void exitLobbyRoute();

	void signUpRoute();
	void logOutRoute();
	void startApp();
};