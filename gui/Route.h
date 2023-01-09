#pragma once
#include <string>
#include <vector>
#include "PlayerQString.h"
#include "CredentialErrors.h"
class Route
{
	std::string m_sessionKey;
	long m_gameId;
public:
	std::string getQuestionTypeNumerical();
	std::array<std::string, 5> getQuestionTypeVariants();
	std::vector<std::pair<Color::ColorEnum, int>> sendResponseNumericalEt1(int resp, int time, Color::ColorEnum color);
	std::pair<int, Color::ColorEnum> chooseRegion(int id, Color::ColorEnum color);


	bool leaveLobby();
	void enterLobby(int type, std::vector<std::shared_ptr<PlayerQString>>& players);

	CredentialErrors login(std::string username, std::string password);
	std::string getSessionKey();
	CredentialErrors signUp(std::string username, std::string password, std::string name);
	bool logOut();


};