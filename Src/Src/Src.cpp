#include <iostream>
#include <memory>

#include "Database.h"

#include <crow.h>
#include "utils.h"
#include "GameLogic.h"

#include "ManualTests.h"
#include <unordered_map>
#include <unordered_set>

void GameLobby(crow::SimpleApp& app, const  std::unordered_map< std::string, Player>& playersOnline)
{


}

void routeFct()
{
	//Acest este defapt Lobby -ul 
	Database db("file.db");
	crow::SimpleApp app;

	std::unordered_map< std::string, Player> playersOnline;
	std::unordered_map<std::string, GameLogic> gamesActive;
	std::unordered_map< std::string, Player> twoPlayers;

	auto& queueTwoPlayers = CROW_ROUTE(app, "/queueTwoPlayerGame").methods(crow::HTTPMethod::Put);

	queueTwoPlayers([&playersOnline, &twoPlayers](const crow::request& req) {

		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");
	if (playersOnline.find(usernameIter->second) != playersOnline.end())
	{
		//std::cout << playersOnline.at(usernameIter->second);
		std::string key = usernameIter->second;
		twoPlayers.insert({ key, playersOnline.at(key) });
	}
	else
	{
		return crow::response(400);
	}
	//twoPlayers.insert({ usernameIter->second,playersOnline.at(usernameIter->second )});

	if (twoPlayers.size() != 2)
	{
		return crow::response(201); // 201 means that the player is queued
	}
	else
	{

		return crow::response(200); // the game stars when there are two players in the queue
	}
		});

	auto& exitQueue = CROW_ROUTE(app, "/exitQueueTwoPlayersGame").methods(crow::HTTPMethod::PUT);

	exitQueue([&playersOnline, &twoPlayers](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");
	twoPlayers.erase(usernameIter->second);

	return crow::response(200);
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
		return crow::response(401);
	}
	else
	{
		playersOnline[usernameIter->second] = (Player(usernameIter->second, ""));
		crow::json::wvalue playerInstance;
		playerInstance["firstname"] = usernameIter->second;
		playerInstance["lastname"] = playersOnline[usernameIter->second].getLastName();
		return crow::response(playerInstance);
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

	GameLobby(app, playersOnline);

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

