#include "Route.h"
#include "utils.h"
#include<string>

Route::Route(Database& db) : m_db{db}
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
			sessionKey = m_playerList.addActivePlayer(account);
		}
		crow::response res;
		res.body = std::to_string(static_cast<int>(check)) + sessionKey;
		res.code = 200;
		return res;
		});
}

void Route::signUpRoute()
{
	auto& login = CROW_ROUTE(m_app, "/signUp")
		.methods(crow::HTTPMethod::Post);
	login([this](const crow::request& req) {
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

void Route::startApp()
{
	m_app.port(18080).multithreaded().run();
}


