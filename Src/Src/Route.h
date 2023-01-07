#pragma once
#include "GameLogic.h"
#include "CredentialErrors.h"
#include "QTypeNumerical.h"
#include "Database.h"
#include <crow.h>
#include "PlayersQueue.h"

class Route
{
	crow::SimpleApp m_app;

	std::shared_ptr<Database> m_db;

	std::shared_ptr<PlayersQueue> m_waitingList;
	std::unordered_map<long, std::shared_ptr<GameLogic>> m_gamesActive;

	void addActiveGame(std::shared_ptr<Lobby> lobby);
public:
	Route();

	void getQuestionTypeNumericalRoute();
	void getQuestionTypeVariantsRoute();


	void loginRoute();

	void enterLobbyRoute();
	void exitLobbyRoute();

	void signUpRoute();
	void logOutRoute();
	void startApp();
}; 