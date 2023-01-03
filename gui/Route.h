#pragma once
#include <string>
#include "CredentialErrors.h"
class Route
{
	std::string m_sessionKey;
public:

	bool leaveLobby();
	int enterTwoPlayersLobby();
	CredentialErrors login(std::string username, std::string password);
	std::string getSessionKey();
	CredentialErrors signUp(std::string username, std::string password, std::string name);
	bool logOut();

};