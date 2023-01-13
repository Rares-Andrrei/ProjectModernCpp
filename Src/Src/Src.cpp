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
	r.chooseRegionRoute();
	r.getQuestionTypeVariantsRoute();
	r.sendResponseQTypeNumericalEt1();
	r.getQuestionTypeNumericalRoute();
	r.exitLobbyRoute();
	r.logOutRoute();
	r.startApp();
}

void board()
{
	Board b(2);
	b.ValidateBasePosition(0);
	b.AddZonaAsBase(0, Color::ColorEnum::Red);
	b.ValidateBasePosition(4);
	b.AddZonaAsBase(4, Color::ColorEnum::Yellow);
	
	//
	b.AddCloseZone(1, Color::ColorEnum::Yellow);
	b.AddCloseZone(3, Color::ColorEnum::Yellow);
	b.AddCloseZone(5, Color::ColorEnum::Red);
	b.AddCloseZone(2, Color::ColorEnum::Red);
	b.AddCloseZone(8, Color::ColorEnum::Red);
	b.AddCloseZone(7, Color::ColorEnum::Red);
	b.AddCloseZone(6, Color::ColorEnum::Blue);
	if (b.ValidateAttackMove(1, Color::ColorEnum::Red))
	{
		b[1]->changeOwner(Color::ColorEnum::Red);
	}
}

int main()
{
	useRoutes();
	//board();
	return 0;
}

