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

	void requestDuelTurn();
	void duelParticipantsRoute();
	void getQuestionTypeVariantsRoute();
	void sendResponseEt2();
	void getQuestionTypeNumericalRouteEt2();

	void getQuestionTypeNumericalRoute();
	void sendResponseQTypeNumericalEt1();
	void chooseRegionRoute();

	void loginRoute();

	void checkValidBasePosition();
	void checkValidRegionPosition();
	void checkValidAttackMove();
	void checkIfBoardIsFull();
	void updateZoneInfo();

	void checkIfPlayerCanUseAdvantages();
	void useAdvantage();

	void updatePlayerInfo();

	void gamesHistoryRoute();
	void enterLobbyRoute();
	void exitLobbyRoute();

	void signUpRoute();
	void logOutRoute();
	void startApp();
};