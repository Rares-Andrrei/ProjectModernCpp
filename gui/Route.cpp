#include "Route.h"
#include <cpr/cpr.h>
#include <iostream>
#include <sstream>
CredentialErrors Route::login(std::string username, std::string password)
{
	auto response = cpr::Post(
		cpr::Url{ "http://localhost:18080/login" },
		cpr::Payload{
			{ "username", username},
			{ "password", password}
		}
	);
	std::stringstream s(std::string(1, response.text[0]));
	int resp;
	s >> resp;
	if (resp == static_cast<int>(CredentialErrors::IncorrectAccount))
	{
		return CredentialErrors::IncorrectAccount;
	}
	else if (resp == static_cast<int>(CredentialErrors::IncorrectPassword))
	{
		return CredentialErrors::IncorrectPassword;
	}
	else if (resp == static_cast<int>(CredentialErrors::Valid))
	{
		response.text.erase(response.text.begin());
		m_sessionKey = response.text;
		return CredentialErrors::Valid;
	}
	else
	{
		return CredentialErrors::Other;
	}
}

CredentialErrors Route::signUp(std::string username, std::string password, std::string name)
{
	auto response = cpr::Post(
		cpr::Url{ "http://localhost:18080/signUp" },
		cpr::Payload{
			{ "username", username},
			{ "password", password},
			{"name", name}
		}
	);
	std::stringstream s(response.text);
	int resp;
	s >> resp;
	if (resp == static_cast<int>(CredentialErrors::NameSize))
	{
		return CredentialErrors::NameSize;
	}
	else if (resp == static_cast<int>(CredentialErrors::UsernameSize))
	{
		return CredentialErrors::UsernameSize;
	}
	else if (resp == static_cast<int>(CredentialErrors::PasswordSize))
	{
		return CredentialErrors::PasswordSize;
	}
	else if (resp == static_cast<int>(CredentialErrors::UserTaken))
	{
		return CredentialErrors::UserTaken;
	}
	else if (resp == static_cast<int>(CredentialErrors::NameTaken))
	{
		return CredentialErrors::NameTaken;
	}
	else if(resp == static_cast<int>(CredentialErrors::Valid))
	{
		return CredentialErrors::Valid;
	}
	else
	{
		return CredentialErrors::Other;
	}
}
