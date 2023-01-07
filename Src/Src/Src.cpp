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
#include "PlayersQueue.h"

long Lobby::currentCount = 0;
void useRoutes()
{
	Route r;
	r.loginRoute();
	r.signUpRoute();
	r.enterLobbyRoute();
	r.getQuestionTypeVariantsRoute();
	r.getQuestionTypeNumericalRoute();
	r.exitLobbyRoute();
	r.logOutRoute();
	r.startApp();
}


int main()
{
	useRoutes();

	return 0;
}

