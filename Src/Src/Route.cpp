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
		m_gamesActive[lobby->getId()]->createDuelOrder();
	}
}

Route::Route()
{
	m_db = std::make_shared<Database>("file.db");
	m_waitingList = std::make_shared<PlayersQueue>();
	m_logger.setMinimumLogLevel(Logger::Level::Info);
	m_logger.log( "Server started", Logger::Level::Info);
}

void Route::requestDuelTurn()
{
	auto& requestDuerlTurn = CROW_ROUTE(m_app, "/requestDuerlTurn")
		.methods(crow::HTTPMethod::Post);
	requestDuerlTurn([this](const crow::request& req) {
	
	auto bodyArgs = parseUrlArgs(req.body);
	auto gameIdIter = bodyArgs.find("gameID");
	auto sessionKeyIter = bodyArgs.find("sessionKey");
	long gameID = std::stoi(gameIdIter->second);
	

	if (gameIdIter->second == "" || sessionKeyIter->second == "")
	{
		return crow::response(404);
	}

	if (m_gamesActive.count(gameID) > 0 && m_waitingList->isActive(sessionKeyIter->second))
	{

		m_gamesActive[gameID]->addWaitingRequest(m_waitingList->getPlayer(sessionKeyIter->second)->getColor());
		m_gamesActive[gameID]->setColorToAttack();
		while (!m_gamesActive[gameID]->allRequestsReady())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		crow::json::wvalue json;
		json["attackerColor"] = Color::ColorToInt(m_gamesActive[gameID]->getAttackerColor());
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		m_gamesActive[gameID]->deleteRequestsReady();
		if (m_waitingList->getPlayer(sessionKeyIter->second)->getColor() == m_gamesActive[gameID]->getAttackerColor())
		{
			m_gamesActive[gameID]->deleteColorToAttack();
		}
		
	
		m_logger.logg(Logger::Level::Info, "Request: ", req.url);
		m_logger.logg(Logger::Level::Info, "Response: ", crow::response(json).code, req.url);
		return crow::response(json);
	}
	return crow::response(404);
		});
}

void Route::sendResponseEt2()
{
	auto& sendResponseVariants = CROW_ROUTE(m_app, "/sendResponseEt2").methods(crow::HTTPMethod::Post);
	sendResponseVariants([this](const crow::request& req) {

	auto bodyArgs = parseUrlArgs(req.body);
	auto sessionKeyIter = bodyArgs.find("sessionKey");
	auto gameIdIter = bodyArgs.find("gameID");
	auto colorIter = bodyArgs.find("color");
	auto responseIter = bodyArgs.find("response");

	if (gameIdIter->second == "" || sessionKeyIter->second == "" || responseIter->second == "" || colorIter->second == "")
	{
		return crow::response(404);
	}

	long gameID = std::stoi(gameIdIter->second);
	Color::ColorEnum color = Color::getColor(std::stoi(colorIter->second));

	if (m_waitingList->isActive(sessionKeyIter->second) && m_gamesActive.count(gameID) > 0)
	{
		if (color != Color::ColorEnum::None)
		{
			if (m_gamesActive[gameID]->duelDraw())
			{
				auto timeIter = bodyArgs.find("time");
				m_gamesActive[gameID]->setDuelNumericalAnswer(std::stoi(timeIter->second), std::stoi(responseIter->second), color);
			}
			else
			{
				m_gamesActive[gameID]->duelPlayerResponse(color, std::stoi(responseIter->second));
			}
		}

		m_gamesActive[gameID]->addWaitingRequest(m_waitingList->getPlayer(sessionKeyIter->second)->getColor());
		while (!m_gamesActive[gameID]->allRequestsReady())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		m_gamesActive[gameID]->deleteRequestsReady();

		if (color == m_gamesActive[gameID]->getAttackerColor())
		{
			m_gamesActive[gameID]->setDuelPlayerWinner();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));

		Duel::DuelState state = m_gamesActive[gameID]->getDuelState();
		crow::response res;
		if (state != Duel::DuelState::None)
		{
			crow::json::wvalue json;
			if (state == Duel::DuelState::Lose)
			{
				json["duelStatus"] = "Lose"; //aici practic nu castiga nimeni, nu se intampla nimic
				res = json;
				res.code = 200;
				return res;
			}
			else if (state == Duel::DuelState::lifeTaken)
			{
				json["duelStatus"] = "lifeTaken";
				std::vector<std::shared_ptr<Zone>> zones = m_gamesActive[gameID]->getDuelZones();
				auto isBase = std::dynamic_pointer_cast<PlayerBase>(zones[0]);
				Color::ColorEnum color1, color2;
				int zoneId;
				m_gamesActive[gameID]->getDuelingPlayersAndZone(color1, color2, zoneId);
				json["baseId"] = zoneId;
				json["lives"] = isBase->getNumberOfLifesLeft();
				json["score"] = isBase->getScore();
				json["color"] = Color::ColorToInt(isBase->getColor());
				json["attacker"] = Color::ColorToInt(color1); //aici inseamna ca i-a luat o viata din baza si pe client apelezi iar duelu cu ei doi
				json["defender"] = Color::ColorToInt(color2);
				res = json;
				res.code = 200;
				return res;
			}
			else if (state == Duel::DuelState::Draw)
			{
				json["duelStatus"] = "Draw";
				int zoneId;
				Color::ColorEnum color1, color2;
				m_gamesActive[gameID]->getDuelingPlayersAndZone(color1, color2, zoneId);
				json["attacker"] = Color::ColorToInt(color1);
				json["defender"] = Color::ColorToInt(color2);
				res = json;
				res.code = 200;
				return res;
			}
			else if (state == Duel::DuelState::Win)
			{
				json["duelStatus"] = "Win";
				std::vector<std::shared_ptr<Zone>> zones = m_gamesActive[gameID]->getDuelZones(); //aici e un vector pt ca exista si posibilitatea sa fi distrus baza si sa ia mai multe zone
				int zoneNr = 0;
				for (auto zone : zones)
				{
					json["zoneColor" + std::to_string(zoneNr)] = Color::ColorToInt(zone->getColor());
					json["zoneId" + std::to_string(zoneNr)] = m_gamesActive[gameID]->getZoneId(zone);
					json["zoneScore" + std::to_string(zoneNr)] = zone->getScore();

					zoneNr++;
				}
				json["zoneNr"] = zoneNr;
				res = json;
				res.code = 200;
				return res;
			}
		}
	}
	return crow::response(404);
		});
}

void Route::getQuestionTypeNumericalRouteEt2()
{
	auto& getQuestionTypeNumericalEt2 = CROW_ROUTE(m_app, "/getQuestionTypeNumericalEt2")
		.methods(crow::HTTPMethod::Get);
	getQuestionTypeNumericalEt2([this](const crow::request& req) {
	auto bodyArgs = parseUrlArgs(req.body);
	auto gameIdIter = bodyArgs.find("gameID");
	long gameID = std::stoi(gameIdIter->second);
	crow::response res;
	if (m_gamesActive.count(gameID) > 0)
	{
		QTypeNumerical question = m_gamesActive[gameID]->getDuelNumericalQ();
		res.body = question.getQuestion();
		res.code = 200;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		return res;
	}
	res.code = 404;
	return res;
		});

}

void Route::duelParticipantsRoute()
{
	auto& duelParticipants = CROW_ROUTE(m_app, "/duelParticipants").methods(crow::HTTPMethod::Post);
	duelParticipants([this](const crow::request& req) {

	auto bodyArgs = parseUrlArgs(req.body);
	auto gameIdIter = bodyArgs.find("gameID");
	auto sessionKeyIter = bodyArgs.find("sessionKeyIter");
	auto attackerIter = bodyArgs.find("attacker");
	auto regionIdIter = bodyArgs.find("regionId");
	auto end = bodyArgs.end();


	if (gameIdIter->second == "" || sessionKeyIter->second == "" || attackerIter->second == "" || regionIdIter->second == "")
	{
		return crow::response(404);
	}

	long gameID = std::stoi(gameIdIter->second);
	if (m_gamesActive.count(gameID) > 0 && m_waitingList->isActive(sessionKeyIter->second))
	{
		int regionId = std::stoi(regionIdIter->second);
		Color::ColorEnum color = Color::getColor(std::stoi(attackerIter->second));

		if (regionId != -1)
		{
			m_gamesActive[gameID]->setDuel(color, regionId);
		}
		m_gamesActive[gameID]->addWaitingRequest(m_waitingList->getPlayer(sessionKeyIter->second)->getColor());
		while (!m_gamesActive[gameID]->allRequestsReady())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		m_gamesActive[gameID]->deleteRequestsReady();
		Color::ColorEnum color1, color2;
		int zoneId;
		m_gamesActive[gameID]->getDuelingPlayersAndZone(color1, color2, zoneId);
		crow::json::wvalue json;
		json["color1"] = Color::ColorToInt(color1);
		json["color2"] = Color::ColorToInt(color2);
		json["zoneId"] = zoneId;
		crow::response res;
		res.code = 200;
		res = json;
		return res;
	}
	return crow::response(404);

		});
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
	crow::response res;
	crow::json::wvalue json;
	if (check == CredentialErrors::Valid)
	{
		sessionKey = m_waitingList->addActivePlayer(account);
		if (sessionKey == "NULL")
		{
			check = CredentialErrors::AlreadyConnected;
		}
		else
		{
			json["sessionKey"] = sessionKey;
			json["nickname"] = m_waitingList->getPlayer(sessionKey)->getName();
		}
	}
	json["error"] = static_cast<int>(check);
	res = json;
	res.code = 200;
	m_logger.logg(Logger::Level::Info,"Request: ", req.url);
	m_logger.logg(Logger::Level::Info,"Response: ", res.code,req.url);
	
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
		m_logger.logg(Logger::Level::Info, "Request: ", req.url);
		m_logger.logg(Logger::Level::Info, "Response: ", res.code, req.url);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return res;
	}
	
	m_logger.logg(Logger::Level::Error, "Request: ", req.url);
	m_logger.logg(Logger::Level::Error, "Response: ", crow::response(404).code, req.url);
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
		m_logger.logg(Logger::Level::Info, "Request: ", req.url);
		m_logger.logg(Logger::Level::Info, "Response: ", res.code, req.url);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return res;
	}

	m_logger.logg(Logger::Level::Error, "Request: ", req.url);
	m_logger.logg(Logger::Level::Error, "Response: ", crow::response(404).code, req.url);
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
		m_logger.logg(Logger::Level::Info, "Request: ", req.url);
		m_logger.logg(Logger::Level::Info, "Response: ", res.code, req.url);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return res;
	}
	
	m_logger.logg(Logger::Level::Error, "Request: ", req.url);
	m_logger.logg(Logger::Level::Error, "Response: ", crow::response(404).code, req.url);
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
		m_logger.logg(Logger::Level::Info, "Request: ", req.url);
		m_logger.logg(Logger::Level::Info, "Response: ", res.code, req.url);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return res;
	}
	
	m_logger.logg(Logger::Level::Error, "Request: ", req.url);
	m_logger.logg(Logger::Level::Error, "Response: ", crow::response(404).code, req.url);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	return crow::response(404);
		});
}

void Route::updateZoneInfo()
{
	auto& updateZoneInfo = CROW_ROUTE(m_app, "/updateZoneInfo")
		.methods(crow::HTTPMethod::Get);
	updateZoneInfo([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto gameIdIter = bodyArgs.find("gameID");
	auto regionIdIter = bodyArgs.find("regionId");
	auto end = bodyArgs.end();
	long gameID = std::stoi(gameIdIter->second);

	if (m_gamesActive.count(gameID) > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		int regionId = std::stoi(regionIdIter->second);
		auto zoneInfo = m_gamesActive[gameID]->getZoneInfo(regionId);
		auto& [zoneId, zoneColor, zoneScore, zoneLifes] = zoneInfo;
		crow::json::wvalue json;
		crow::response res;
		json["zoneId"] = std::to_string(zoneId);
		json["zoneColor"] = std::to_string(Color::ColorToInt(zoneColor));
		json["zoneScore"] = std::to_string(zoneScore);
		json["zoneLifes"] = std::to_string(zoneLifes);

		res.code = 200;
		res = json;
		m_logger.logg(Logger::Level::Info, "Request: ", req.url);
		m_logger.logg(Logger::Level::Info, "Response: ", res.code, req.url);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return res;
	}
	
	m_logger.logg(Logger::Level::Error, "Request: ", req.url);
	m_logger.logg(Logger::Level::Error, "Response: ", crow::response(404).code, req.url);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	return crow::response(404);
		});
}

void Route::checkIfPlayerCanUseAdvantages()
{
	auto& checkIfPlayerCanUseAdvantages = CROW_ROUTE(m_app, "/checkIfPlayerCanUseAdvantages")
		.methods(crow::HTTPMethod::Get);
	checkIfPlayerCanUseAdvantages([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto gameIdIter = bodyArgs.find("gameID");
	auto colorIter = bodyArgs.find("color");
	auto end = bodyArgs.end();
	long gameID = std::stoi(gameIdIter->second);

	if (m_gamesActive.count(gameID) > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		Color::ColorEnum color = Color::getColor(std::stoi(colorIter->second));
		bool valid = m_gamesActive[gameID]->checkIfPlayerCanUseAdvantages(color);

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

void Route::useAdvantage()
{
	auto& useAdvantage = CROW_ROUTE(m_app, "/useAdvantage")
		.methods(crow::HTTPMethod::Post);
	useAdvantage([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto gameIdIter = bodyArgs.find("gameID");
	auto sessionKeyIter = bodyArgs.find("sessionKey");
	auto advantageTypeIter = bodyArgs.find("advantageType");
	auto stageIter = bodyArgs.find("stage");
	long gameID = std::stoi(gameIdIter->second);
	if (m_gamesActive.count(gameID) > 0 && m_waitingList->isActive(sessionKeyIter->second))
	{
		std::pair<int, int> zoneData = m_gamesActive[gameID]->taxForAdvantage(m_waitingList->getPlayer(sessionKeyIter->second)->getColor());
		crow::json::wvalue json;
		json["zone"] = zoneData.first;
		json["score"] = zoneData.second;
		json["color"] = Color::ColorToInt(m_waitingList->getPlayer(sessionKeyIter->second)->getColor());
		if (stageIter->second == "ET1")
		{
			QTypeNumerical question = m_gamesActive[gameID]->getQuestionTypeNumerical();
			if (advantageTypeIter->second == "fourClose")
			{
				FourCloseAnswers advantage;
				advantage.GenerateVariants(question);
				std::array<int, 4> answers = advantage.getAnswers();
				json["r1"] = answers[0];
				json["r2"] = answers[1];
				json["r3"] = answers[2];
				json["r4"] = answers[3];
				return crow::response(json);
			}
			else if (advantageTypeIter->second == "sugestion")
			{
				json["r"] = AnswerSugestion::useAdvantage(question.getAnswer());
				return crow::response(json);
			}
		}
		else if (stageIter->second == "ET2")
		{
			if (advantageTypeIter->second == "fourClose")
			{
				FourCloseAnswers advantage;
				advantage.GenerateVariants(m_gamesActive[gameID]->getDuelNumericalQ());
				std::array<int, 4> answers = advantage.getAnswers();
				json["r1"] = answers[0];
				json["r2"] = answers[1];
				json["r3"] = answers[2];
				json["r4"] = answers[3];
				return crow::response(json);
			}
			else if (advantageTypeIter->second == "sugestion")
			{
				QTypeNumerical question = m_gamesActive[gameID]->getDuelNumericalQ();
				json["r"] = AnswerSugestion::useAdvantage(question.getAnswer());
				return crow::response(json);
			}
			else if (advantageTypeIter->second == "50-50")
			{
				QTypeVariants question = m_gamesActive[gameID]->getQuestionTypeVariants();
				AnswerFiftyFifty advantage(question);
				std::array<std::string, 2> options = advantage.AdvantageUtility();
				json["r1"] = options[0];
				json["r2"] = options[1];
				return crow::response(json);
			}
		}
	}
	return crow::response();
		});



}

void Route::updatePlayerInfo()
{
	auto& updatePlayerInfo = CROW_ROUTE(m_app, "/updatePlayerInfo")
		.methods(crow::HTTPMethod::Get);
	updatePlayerInfo([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto gameIdIter = bodyArgs.find("gameID");
	auto end = bodyArgs.end();
	long gameID = std::stoi(gameIdIter->second);

	if (m_gamesActive.count(gameID) > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));


		crow::json::wvalue json = GameLogic::playersToJson(m_gamesActive[gameID]->getPlayers());
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
		m_logger.logg(Logger::Level::Info, "Request: ", req.url);
		m_logger.logg(Logger::Level::Info, "Response: ", res.code, req.url);
		return res;
	}
	else
	{
		
		m_logger.logg(Logger::Level::Error, "Request: ", req.url);
		m_logger.logg(Logger::Level::Error, "Response: ", crow::response(404).code, req.url);
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
		m_logger.logg(Logger::Level::Info, "Request: ", req.url);
		m_logger.logg(Logger::Level::Info, "Response: ", crow::response(json).code, req.url);
		return crow::response(json);
	}
	m_logger.logg(Logger::Level::Warning, "Request: ", req.url);
	m_logger.logg(Logger::Level::Warning, "Response: ", crow::response(201).code, req.url);
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
		m_logger.logg(Logger::Level::Error, "Request: ", req.url);
		m_logger.logg(Logger::Level::Error, "Response: ", crow::response(404).code, req.url);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
		m_logger.logg(Logger::Level::Info, "Request: ", req.url);
		m_logger.logg(Logger::Level::Info, "Response: ", resp.code, req.url);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return resp;
	}
	else
	{
	
		m_logger.logg(Logger::Level::Error, "Request: ", req.url);	
		m_logger.logg(Logger::Level::Error, "Response: ", crow::response(404).code, req.url);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return crow::response(404);
	}
	m_logger.logg(Logger::Level::Error, "Request: ", req.url);
	m_logger.logg(Logger::Level::Error, "Response: ", crow::response(404).code, req.url);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
		m_logger.logg(Logger::Level::Info, "Request: ", req.url);
		m_logger.logg(Logger::Level::Info, "Response: ", res.code, req.url);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return res;
	}
	//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	m_logger.logg(Logger::Level::Error, "Request: ", req.url);
	m_logger.logg(Logger::Level::Error, "Response: ", crow::response(404).code, req.url);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
	m_logger.logg(Logger::Level::Info, "Request: ", req.url);
	m_logger.logg(Logger::Level::Info, "Response: ", crow::response(200).code, req.url);
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
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
		m_logger.logg(Logger::Level::Info, "Request: ", req.url);
		m_logger.logg(Logger::Level::Info, "Response: ", res.code, req.url);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return res;
	}
	res.code = 404;
	//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	m_logger.logg(Logger::Level::Error, "Request: ", req.url);
	m_logger.logg(Logger::Level::Error, "Response: ", res.code, req.url);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
		m_logger.logg(Logger::Level::Info, "Request: ", req.url);
		m_logger.logg(Logger::Level::Info, "Response: ", res.code, req.url);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		return res;
	}
	else
	{
		res.code = 404;
	}
	
	m_logger.logg(Logger::Level::Error, "Request: ", req.url);
	m_logger.logg(Logger::Level::Error, "Response: ", res.code, req.url);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
	m_logger.logg(Logger::Level::Info, "Request: ", req.url);
	m_logger.logg(Logger::Level::Info, "Response: ", res.code, req.url);
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
	m_logger.logg(Logger::Level::Info, "Request: ", req.url);
	m_logger.logg(Logger::Level::Info, "Response: ", res.code, req.url);
	return res;
		});
}

void Route::startApp()
{
	m_app.port(18080).multithreaded().run();
}