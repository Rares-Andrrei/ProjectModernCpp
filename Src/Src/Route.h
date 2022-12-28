#pragma once

#include "CredentialErrors.h"
#include "Database.h"
#include <crow.h>
#include "ActivePlayers.h"

class Route
{
	Database& m_db;
	crow::SimpleApp m_app;
	ActivePlayers m_playerList;
public:
	Route(Database& db);
	void loginRoute();
	void signUpRoute();
	void startApp();
};