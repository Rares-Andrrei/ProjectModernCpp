#include "Route.h"
#include "utils.h"
#include "MatchInfo.h"
#include <thread>
#include<string>

void Route::addActiveGame(std::shared_ptr<Lobby> lobby)
{
	if (m_gamesActive.count(lobby->getId()) == 0)
	{
		m_gamesActive[lobby->getId()] = std::make_shared<GameLogic>(GameLogic(static_cast<int>(lobby->getType()), m_db));
		std::vector<std::shared_ptr<Player>> players = lobby->getPlayers();
		for (auto player : players)
		{
			m_gamesActive[lobby->getId()]->addPlayer(player);
		}
	}
}

Route::Route()
{
	m_db = std::make_shared<Database>("file.db");
	m_waitingList = std::make_shared<PlayersQueue>();
}

void Route::loginRoute()
{
	auto& login = CROW_ROUTE(m_app, "/login")
		.methods(crow::HTTPMethod::Post);
	login([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto usernameIter = bodyArgs.find("username");
	auto passwordIter = bodyArgs.find("password");
	Account account;
	account.setPassword(passwordIter->second);
	account.setUsername(usernameIter->second);
	CredentialErrors check = m_db->loginUser(account);
	std::string sessionKey;
	if (check == CredentialErrors::Valid)
	{
		sessionKey = m_waitingList->addActivePlayer(account);
		if (sessionKey == "NULL")
		{
			check = CredentialErrors::AlreadyConnected;
		}
	}
	crow::response res;
	res.body = std::to_string(static_cast<int>(check)) + sessionKey;
	res.code = 200;

	return res;
		});
}

void Route::checkValidBasePosition()
{
	auto& checkValidBasePosition = CROW_ROUTE(m_app, "/checkValidBasePosition")
		.methods(crow::HTTPMethod::Get);
	checkValidBasePosition([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto gameIdIter = bodyArgs.find("gameID");
	auto regionIdIter = bodyArgs.find("regionId");
	auto end = bodyArgs.end();
	long gameID = std::stoi(gameIdIter->second);

	if (m_gamesActive.count(gameID) > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		int regionId = std::stoi(regionIdIter->second);
		bool valid = m_gamesActive[gameID]->ValidateBasePosition(regionId);

		crow::json::wvalue json;
		if (valid == true)
		{
			json["valid"] = "true";
		}
		else
		{
			json["valid"] = "false";
		}
		crow::response res;
		res.code = 200;
		res = json;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return res;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	return crow::response(404);

		});
}

void Route::checkValidRegionPosition()
{
	auto& checkValidRegionPosition = CROW_ROUTE(m_app, "/checkValidRegionPosition")
		.methods(crow::HTTPMethod::Get);
	checkValidRegionPosition([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto gameIdIter = bodyArgs.find("gameID");
	auto colorIter = bodyArgs.find("color");
	auto regionIdIter = bodyArgs.find("regionId");
	auto end = bodyArgs.end();
	long gameID = std::stoi(gameIdIter->second);

	if (m_gamesActive.count(gameID) > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		int regionId = std::stoi(regionIdIter->second);
		Color::ColorEnum color = Color::getColor(std::stoi(colorIter->second));
		bool valid = m_gamesActive[gameID]->ValidateRegionPosition(regionId, color);

		crow::json::wvalue json;
		if (valid == true)
		{
			json["valid"] = "true";
		}
		else
		{
			json["valid"] = "false";
		}
		crow::response res;
		res.code = 200;
		res = json;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return res;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	return crow::response(404);
		});
}

void Route::checkValidAttackMove()
{
	auto& checkValidAttackMove = CROW_ROUTE(m_app, "/checkValidAttackMove")
		.methods(crow::HTTPMethod::Get);
	checkValidAttackMove([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto gameIdIter = bodyArgs.find("gameID");
	auto colorIter = bodyArgs.find("color");
	auto regionIdIter = bodyArgs.find("regionId");
	auto end = bodyArgs.end();
	long gameID = std::stoi(gameIdIter->second);

	if (m_gamesActive.count(gameID) > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		int regionId = std::stoi(regionIdIter->second);
		Color::ColorEnum color = Color::getColor(std::stoi(colorIter->second));
		bool valid = m_gamesActive[gameID]->ValidateAttackMove(regionId, color);

		crow::json::wvalue json;
		if (valid == true)
		{
			json["valid"] = "true";
		}
		else
		{
			json["valid"] = "false";
		}
		crow::response res;
		res.code = 200;
		res = json;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return res;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	return crow::response(404);
		});
}

void Route::checkIfBoardIsFull()
{
	auto& checkIfBoardIsFull = CROW_ROUTE(m_app, "/checkIfBoardIsFull")
		.methods(crow::HTTPMethod::Get);
	checkIfBoardIsFull([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto gameIdIter = bodyArgs.find("gameID");
	auto end = bodyArgs.end();
	long gameID = std::stoi(gameIdIter->second);

	if (m_gamesActive.count(gameID) > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		bool valid = m_gamesActive[gameID]->CheckIfBoardIsFull();

		crow::json::wvalue json;
		if (valid == true)
		{
			json["valid"] = "true";
		}
		else
		{
			json["valid"] = "false";
		}
		crow::response res;
		res.code = 200;
		res = json;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return res;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	return crow::response(404);
		});
}

void Route::gamesHistoryRoute()
{
	auto& getHistoryRoute = CROW_ROUTE(m_app, "/getMatchHistory")
		.methods(crow::HTTPMethod::Get);
	getHistoryRoute([this](const crow::request& req) {

		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto sessionKeyIter = bodyArgs.find("sessionKey");

	if (m_waitingList->isActive(sessionKeyIter->second))
	{
		std::string playerName = m_waitingList->getPlayer(sessionKeyIter->second)->getName();
		std::list<MatchInfo> matchList = m_db->getMatchHistory(playerName);
		int matchesNr = 0;
		crow::json::wvalue json;
		for (const auto& match : matchList)
		{
			json["Date" + std::to_string(matchesNr)] = match.getDate();
			json["Place1" + std::to_string(matchesNr)] = match.getFirstPlace();
			json["Place2" + std::to_string(matchesNr)] = match.getSecondPlace();
			json["Place3" + std::to_string(matchesNr)] = match.getThirdPlace();
			json["Place4" + std::to_string(matchesNr)] = match.getFourthPlace();
			matchesNr++;
		}
		json["MatchesNr"] = matchesNr;
		crow::response res;
		res.code = 200;
		res = json;
		return res;
	}
	else
	{
		return crow::response(404);
	}
		});

}

void Route::enterLobbyRoute()
{
	auto& enterLobbyRoute = CROW_ROUTE(m_app, "/enterLobby").methods(crow::HTTPMethod::Post);
	enterLobbyRoute([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto sessionKeyIter = bodyArgs.find("sessionKey");
	auto lobbyTypeIter = bodyArgs.find("lobbyType");
	Lobby::LobbyType lobbyType = Lobby::stringToLobbyType(lobbyTypeIter->second);
	std::shared_ptr<Lobby> lobby = m_waitingList->addPlayerToLobby(sessionKeyIter->second, lobbyType);
	while (lobby->playersInLobby() < static_cast<int>(lobbyType) && lobby->existInLobby(sessionKeyIter->second))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	crow::response resp;
	if (lobby->existInLobby(sessionKeyIter->second))
	{
		addActiveGame(lobby);
		crow::json::wvalue json = lobby->getPlayersData();
		m_waitingList->deleteLobby(lobby);
		return crow::response(json);
	}
	return crow::response(201);
		});
}

void Route::sendResponseQTypeNumericalEt1()
{
	auto& sendResponse = CROW_ROUTE(m_app, "/sendNumericalResponseEt1").methods(crow::HTTPMethod::Post);
	sendResponse([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto sessionKeyIter = bodyArgs.find("sessionKey");
	auto gameIdIter = bodyArgs.find("gameID");
	auto colorIter = bodyArgs.find("color");
	auto responseIter = bodyArgs.find("response");
	auto timeIter = bodyArgs.find("time");
	if (gameIdIter->second == "" || sessionKeyIter->second == "" || responseIter->second == "" || timeIter->second == "" || colorIter->second == "")
	{
		return crow::response(404);
	}

	int gameID = std::stoi(gameIdIter->second);

	if (m_waitingList->isActive(sessionKeyIter->second) && m_gamesActive.count(gameID) > 0)
	{
		m_gamesActive[gameID]->setPlayerNumericalAnswer(std::stoi(timeIter->second), std::stoi(responseIter->second), Color::getColor(std::stoi(colorIter->second)));
		while (!m_gamesActive[gameID]->NumericalAnswersReady())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		std::vector<std::shared_ptr<Player>> rankingList = m_gamesActive[gameID]->getWinnerList();
		crow::json::wvalue playesData = GameLogic::playersToJson(rankingList);
		crow::response resp = playesData;
		resp.code = 200;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return resp;
	}
	else
	{
		return crow::response(404);
	}
	return crow::response(404);
		});
}

void Route::chooseRegionRoute()
{
	auto& chooseRegion = CROW_ROUTE(m_app, "/chooseRegion").methods(crow::HTTPMethod::Post);
	chooseRegion([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto gameIdIter = bodyArgs.find("gameID");
	auto colorIter = bodyArgs.find("color");
	auto regionIdIter = bodyArgs.find("regionId");
	long gameID = std::stoi(gameIdIter->second);
	if (m_gamesActive.count(gameID) > 0)
	{
		int regionId = std::stoi(regionIdIter->second);
		Color::ColorEnum color = Color::getColor(std::stoi(colorIter->second));
		if (regionId != -1)
		{
			m_gamesActive[gameID]->updateZone(regionId, color);
		}
		m_gamesActive[gameID]->addWaitingRequest(color);
		while (!m_gamesActive[gameID]->checkZoneUpdates() || !m_gamesActive[gameID]->allRequestsReady())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		m_gamesActive[gameID]->deleteRequestsReady();

		std::pair<int, Color::ColorEnum> updatedRegion = m_gamesActive[gameID]->getUpdatedZone();
		crow::json::wvalue json;
		json["zoneId"] = updatedRegion.first;
		json["zoneColor"] = Color::ColorToInt(updatedRegion.second);
		crow::response res;
		res.code = 200;
		res = json;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return res;
	}
	return crow::response(404);

		});
}

void Route::exitLobbyRoute()
{
	auto& exitQueue = CROW_ROUTE(m_app, "/eliminatePlayerFromQueue").methods(crow::HTTPMethod::PUT);
	exitQueue([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto sessionKeyIter = bodyArgs.find("sessionKey");
	m_waitingList->kickPlayerFromLobby(sessionKeyIter->second);
	return crow::response(200);
		});
}

void Route::getQuestionTypeNumericalRoute()
{
	auto& getQuestionTypeNumerical = CROW_ROUTE(m_app, "/getQuestionTypeNumerical")
		.methods(crow::HTTPMethod::Get);
	getQuestionTypeNumerical([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto gameIdIter = bodyArgs.find("gameID");
	long gameID = std::stoi(gameIdIter->second);
	crow::response res;
	if (m_gamesActive.count(gameID) > 0)
	{
		QTypeNumerical question = m_gamesActive[gameID]->getQuestionTypeNumerical();
		res.body = question.getQuestion();
		res.code = 200;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		return res;
	}
	res.code = 404;
	return res;
		});
}

void Route::getQuestionTypeVariantsRoute()
{
	auto& getQuestionTypeVariants = CROW_ROUTE(m_app, "/getQuestionTypeVariants")
		.methods(crow::HTTPMethod::Get);
	getQuestionTypeVariants([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto gameIdIter = bodyArgs.find("gameID");
	long gameID = std::stoi(gameIdIter->second);
	crow::response res;
	if (m_gamesActive.count(gameID) > 0)
	{
		QTypeVariants question = m_gamesActive[gameID]->getQuestionTypeVariants();
		crow::json::wvalue json;
		json["question"] = question.getQuestion();
		json["var1"] = question.getVariant<0>();
		json["var2"] = question.getVariant<1>();
		json["var3"] = question.getVariant<2>();
		json["var4"] = question.getVariant<3>();
		res.code = 200;
		res = json;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		return res;
	}
	else
	{
		res.code = 404;
	}
	return res;
		});
}

void Route::signUpRoute()
{
	auto& signUp = CROW_ROUTE(m_app, "/signUp")
		.methods(crow::HTTPMethod::Post);
	signUp([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto usernameIter = bodyArgs.find("username");
	auto passwordIter = bodyArgs.find("password");
	auto nameIter = bodyArgs.find("name");

	Account account(usernameIter->second, passwordIter->second, nameIter->second);
	CredentialErrors check = m_db->registerUser(account);
	crow::response res;

	res.body = std::to_string(static_cast<int>(check));
	res.code = 200;
	return res;
		});
}

void Route::logOutRoute()
{
	auto& logOut = CROW_ROUTE(m_app, "/logOut")
		.methods(crow::HTTPMethod::Put);
	logOut([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto sessionKey = bodyArgs.find("sessionKey");
	m_waitingList->logOutPlayer(sessionKey->second);
	crow::response res;
	res.code = 200;
	return res;
		});
}

void Route::startApp()
{
	m_app.port(18080).multithreaded().run();
}