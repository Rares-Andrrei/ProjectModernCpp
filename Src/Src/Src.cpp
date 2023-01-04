#include <iostream>
#include <memory>

#include "Database.h"

#include <crow.h>
#include "utils.h"
#include "GameLogic.h"

#include "ManualTests.h"
#include <unordered_map>
#include <unordered_set>

#include <thread>
#include <chrono>

#include "Route.h"
#include "Players.h"


void useRoutes()
{
	Database db("file.db");
	std::shared_ptr<Players> playerList = std::make_shared<Players>();
	Route r(db, playerList);
	r.loginRoute();
	r.signUpRoute();
	r.enterTwoPlayersLobby();
	r.exitTwoPlayersLobby();
	r.logOutRoute();
	r.startApp();
}


int main()
{
	useRoutes();

	return 0;
}

