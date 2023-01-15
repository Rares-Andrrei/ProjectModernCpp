#include <iostream>
#include <memory>

#include "Database.h"

#include <crow.h>
#include "utils.h"
#include "GameLogic.h"

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
	r.gamesHistoryRoute();
	r.checkValidBasePosition();
	r.checkValidRegionPosition();
	r.checkValidAttackMove();
	r.checkIfBoardIsFull();
	r.requestDuelTurn();
	r.duelParticipantsRoute();
	r.sendResponseEt2();
	r.getQuestionTypeNumericalRouteEt2();
	r.updateZoneInfo();
	r.checkIfPlayerCanUseAdvantages();
	r.updatePlayerInfo();
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
	if (b.ValidateAttackMove(1, Color::ColorEnum::Blue))
	{
		b[1]->changeOwner(Color::ColorEnum::Red);
		std::cout << "da\n";
	}
	else std::cout << "nu\n";

	if (b.ValidateAttackMove(3, Color::ColorEnum::Blue))
	{
		b[1]->changeOwner(Color::ColorEnum::Red);
		std::cout << "da\n";
	}
	else std::cout << "nu\n";
}

int main()
{
	useRoutes();
	//board();
	return 0;
}

