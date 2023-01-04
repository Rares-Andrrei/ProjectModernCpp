#pragma once
#include <string>
#include <vector>
#include "PlayersInstance.h"
#include "CredentialErrors.h"
class Route
{
	std::string m_sessionKey;
	int m_gameId;
public:
	//std::string getQuestionTypeNuemrical();

	bool leaveLobby();
	void enterLobby(int type, std::vector<Player>& players);

	int enterTwoPlayersLobby();
	CredentialErrors login(std::string username, std::string password);
	std::string getSessionKey();
	CredentialErrors signUp(std::string username, std::string password, std::string name);
	bool logOut();


};