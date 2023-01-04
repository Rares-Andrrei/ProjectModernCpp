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
	std::unordered_map<long, std::shared_ptr<GameLogic>> m_gamesActive;

	void addActiveGame(std::shared_ptr<Lobby> lobby);
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