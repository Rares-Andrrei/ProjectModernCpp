#pragma once
#include "GameLogic.h"
#include "CredentialErrors.h"
#include "QTypeNumerical.h"
#include "Database.h"
#include <crow.h>
#include "PlayersQueue.h"
#include<iostream>
#include<fstream>
#include"../../Logging/Logging/Logger.h"

class Route
{
	crow::SimpleApp m_app;

	std::shared_ptr<Database> m_db;

	std::shared_ptr<PlayersQueue> m_waitingList;
	std::unordered_map<long, std::shared_ptr<GameLogic>> m_gamesActive;
	std::ofstream m_logFile{ "serverLog.log",std::ios::app };
	Logger m_logger{ m_logFile };
	void addActiveGame(std::shared_ptr<Lobby> lobby);
public:
	Route();

	void requestDuelTurn();

	void getQuestionTypeNumericalRoute();
	void getQuestionTypeVariantsRoute();
	void sendResponseQTypeNumericalEt1();
	void chooseRegionRoute();

	void loginRoute();

	void checkValidBasePosition();
	void checkValidRegionPosition();
	void checkValidAttackMove();
	void checkIfBoardIsFull();
	void updateZoneInfo();

	void gamesHistoryRoute();
	void enterLobbyRoute();
	void exitLobbyRoute();

	void signUpRoute();
	void logOutRoute();
	void startApp();
};