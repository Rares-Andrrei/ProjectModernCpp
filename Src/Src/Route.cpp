#include "Route.h"
#include "utils.h"
#include<string>

void Route::addActiveGame(std::shared_ptr<Lobby> lobby)
{
	if (m_gamesActive.count(lobby->getId()) == 0)
	{
		m_gamesActive[lobby->getId()] = std::make_shared<GameLogic>(GameLogic(static_cast<int>(lobby->getType())));
		std::vector<std::shared_ptr<Player>> players = lobby->getPlayers();
		for (auto player : players)
		{
			m_gamesActive[lobby->getId()]->addPlayer(player);
		}
	}
}

Route::Route(Database& db, std::shared_ptr<PlayersQueue> players) : m_db{db}, m_waitingList{players}
{

}

void Route::loginRoute()
{
	auto& login = CROW_ROUTE(m_app, "/login")
		.methods(crow::HTTPMethod::Post);
	login([this](const crow::request& req){
		auto bodyArgs = parseUrlArgs(req.body);
		auto usernameIter = bodyArgs.find("username");
		auto passwordIter = bodyArgs.find("password");
		Account account;
		account.setPassword(passwordIter->second);
		account.setUsername(usernameIter->second);
		CredentialErrors check = m_db.loginUser(account);
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
			//wait
		}
		crow::response resp;
		if (lobby->existInLobby(sessionKeyIter->second))
		{
			addActiveGame(lobby);
			//m_waitingList->deleteLobby(lobby);
			crow::json::wvalue json = lobby->getPlayersData();
			return crow::response(json);
		}
		return crow::response(201);
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



//void Route::getQuestionTypeNumericalRoute()
//{
//	auto& getQuestionTypeNumerical = CROW_ROUTE(m_app, "/getQuestionTypeNumerical")
//		.methods(crow::HTTPMethod::Get);
//	getQuestionTypeNumerical([this](const crow::request& req) {
//	crow::response res;
//	res.body = m_questionTypeNumerical.getQuestion();
//	res.code = 200;
//	return res;
//		});
//}

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
	CredentialErrors check = m_db.registerUser(account);
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


