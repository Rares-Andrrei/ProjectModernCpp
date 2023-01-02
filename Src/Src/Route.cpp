#include "Route.h"
#include "utils.h"
#include<string>

Route::Route(Database& db, std::shared_ptr<Players> players) : m_db{db}, m_players{players}
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
			sessionKey = m_players->addActivePlayer(account);
		}
		crow::response res;
		res.body = std::to_string(static_cast<int>(check)) + sessionKey;
		res.code = 200;
		return res;
		});
}

void Route::enterTwoPlayersLobby()
{

	auto& queueTwoPlayers = CROW_ROUTE(m_app, "/queueTwoPlayerGame").methods(crow::HTTPMethod::Put);
	queueTwoPlayers([this](const crow::request& req) {

		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto sessionKeyIter = bodyArgs.find("sessionKey");
	if (m_players->isActive(sessionKeyIter->second))
	{
		std::string key = sessionKeyIter->second;
		twoPlayers.push_back(m_players->getPlayer(key));
	}
	if (twoPlayers.size() < 2)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return crow::response(201); // 201 means that the player is queued
	}
	else
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return crow::response(200); // the game stars when there are two players in the queue
	}
		});
}

void Route::exitTwoPlayersLobby()
{
	auto& exitQueue = CROW_ROUTE(m_app, "/eliminatePlayerFromQueue").methods(crow::HTTPMethod::PUT);
	exitQueue([this](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto sessionKeyIter = bodyArgs.find("sessionKey");
	std::string playerName = m_players->getPlayer(sessionKeyIter->second)->getName();
	for (auto& it : twoPlayers)
	{
		if (it->getName() == playerName)
		{
			twoPlayers.remove(it);
			return crow::response(200);
		}
	}
	return crow::response(200);
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
	m_players->logOutPlayer(sessionKey->second);
	crow::response res;
	res.code = 200;
	return res;
		});
}

void Route::startApp()
{
	m_app.port(18080).multithreaded().run();
}


