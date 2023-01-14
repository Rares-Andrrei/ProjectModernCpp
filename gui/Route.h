#pragma once
#include <string>
#include <vector>
#include "PlayerQString.h"
#include "CredentialErrors.h"
#include <queue>
class Route
{
	std::string m_sessionKey;
	long m_gameId;
public:
	std::string getQuestionTypeNumerical();
	std::array<std::string, 5> getQuestionTypeVariants();
	std::queue<std::pair<Color::ColorEnum, int>> sendResponseNumericalEt1(int resp, int time, Color::ColorEnum color);
	std::pair<int, Color::ColorEnum> chooseRegion(int id, Color::ColorEnum color);

	Color::ColorEnum getAttackerColor();

	bool checkValidBasePosition(int ZoneId);
	bool checkValidRegionPosition(int ZoneId, const Color::ColorEnum& color);
	bool checkValidAttackMove(int ZoneId, const Color::ColorEnum& color);
	bool checkIfBoardIsFull();
	std::tuple<int, Color::ColorEnum, int, int> updateZoneInfo(int ZoneId);

	bool leaveLobby();
	void enterLobby(int type, std::vector<std::shared_ptr<PlayerQString>>& players);

	std::list<std::array<std::string, 5>> getMatchHistoryRoute();

	CredentialErrors login(std::string username, std::string password, QString& setNickname);
	std::string getSessionKey();
	CredentialErrors signUp(std::string username, std::string password, std::string name);
	bool logOut();


};