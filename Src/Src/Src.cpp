#include <iostream>
#include <memory>

#include "Database.h"

#include <crow.h>
#include "utils.h"
#include "GameLogic.h"

#include "ManualTests.h"
#include <unordered_map>
#include <unordered_set>

void routeFct()
{
	//Acest este defapt Lobby -ul 
	Database db("file.db");
	crow::SimpleApp app;

	std::unordered_map< std::string, std::shared_ptr<Player>> playersOnline;
	std::vector<GameLogic> gamesActive;

	CROW_ROUTE(app, "/")([] {
		return "Hallo guys";
		});

	auto& verifyLoginInfo = CROW_ROUTE(app, "/verifylogininfo")
		.methods(crow::HTTPMethod::Put);

	verifyLoginInfo([&db, &playersOnline](const crow::request& req) {

		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");
	auto passwordIter = bodyArgs.find("password");

	Account testAccount;
	testAccount.setPassword(passwordIter->second);
	testAccount.setUsername(usernameIter->second);

	bool result = db.loginUser(testAccount);
	if (result == false)
	{
		return crow::response(400);
	}
	else
	{
		playersOnline[usernameIter->second] = std::move(std::make_shared<Player>(Player(usernameIter->second, "")));
		return crow::response(200);
	}
		});

	//create a logout route
	auto& logout = CROW_ROUTE(app, "/logout")
		.methods(crow::HTTPMethod::Put);
	logout([&db, &playersOnline](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");
	
	playersOnline.erase(usernameIter->second);
	
	return crow::response(200);

		});


	auto& registerUser = CROW_ROUTE(app, "/register")
		.methods(crow::HTTPMethod::Put);

	registerUser([&db](const crow::request& req) {

		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto nicknameIter = bodyArgs.find("nickname");
	auto usernameIter = bodyArgs.find("username");
	auto passwordIter = bodyArgs.find("password");

	Account testAccount;
	testAccount.setNickName(nicknameIter->second);
	testAccount.setPassword(passwordIter->second);
	testAccount.setUsername(usernameIter->second);

	bool result = db.registeUser(testAccount);
	if (result == false)
	{
		return crow::response(400);
	}
	else
	{
		return crow::response(200);
	}
		});


	auto& validateUsername = CROW_ROUTE(app, "/validateusername")
		.methods(crow::HTTPMethod::Put);

	validateUsername([&db](const crow::request& req) {

		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");

	bool result = db.checkUsername(usernameIter->second);
	if (result == true)
	{
		return crow::response(400);
	}
	else
	{
		return crow::response(200);
	}
		});

	app.port(18080).multithreaded().run();
}


int main()
{
	testQuest();
	routeFct();
	//QuestionManager questions;
	//Board b;
	//questions.addQFiles("QuestionFile/QTypeVariants.txt", "QuestionFile/QTypeNumerical.txt");
	//TestSmartPointers();
	//testQuestionManager(questions);
	//testAnswerFiftyFifty(questions);
	//testZoneSiBoard(questions);
	//testPlayer();
	//testChooseBase(b, questions);
	//testDatabase();

	return 0;
}

