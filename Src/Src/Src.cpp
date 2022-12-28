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



void useRoutes()
{
	Database db("file.db");
	Route r(db);
	r.loginRoute();
	r.signUpRoute();
	r.startApp();
}


int main()
{
	useRoutes();

	return 0;
}

