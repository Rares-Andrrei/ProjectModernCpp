#pragma once
#include <string>
#include "CredentialErrors.h"
class Route
{
	std::string m_sessionKey;
public:
	CredentialErrors login(std::string username, std::string password);
	CredentialErrors signUp(std::string username, std::string password, std::string name);

};