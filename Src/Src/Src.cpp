#include "Route.h"

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
	r.useAdvantage();
	r.updatePlayerInfo();
	r.startApp();
}

int main()
{
	useRoutes();
	return 0;
}