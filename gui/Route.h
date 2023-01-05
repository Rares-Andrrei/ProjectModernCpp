#pragma once
#include <string>
#include <vector>
#include "PlayersInstance.h"
#include "CredentialErrors.h"
#include "PlayerQString.h"
class Route
{
	std::string m_sessionKey;
	long m_gameId;
public:
	//std::string getQuestionTypeNuemrical();

	bool leaveLobby();
	void enterLobby(int type, std::vector<PlayerQString>& players);

	CredentialErrors login(std::string username, std::string password);
	std::string getSessionKey();
	CredentialErrors signUp(std::string username, std::string password, std::string name);
	bool logOut();


};