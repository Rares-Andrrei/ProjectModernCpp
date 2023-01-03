#include "Route.h"
#include <cpr/cpr.h>
#include <iostream>
#include <sstream>

std::string Route::getSessionKey()
{
	return m_sessionKey;
}

bool Route::leaveLobby()
{
	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/eliminatePlayerFromQueue" },
		cpr::Payload{
			{ "sessionKey", m_sessionKey}
		});
	return response.status_code == 200;
}

int Route::enterTwoPlayersLobby()
{
	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/queueTwoPlayerGame" },
		cpr::Payload{
			{ "sessionKey", m_sessionKey}
		});
	return response.status_code;
}

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

	switch (resp)
	{
	case static_cast<int>(CredentialErrors::IncorrectAccount):
		return CredentialErrors::IncorrectAccount;
	case static_cast<int>(CredentialErrors::IncorrectPassword):
		return CredentialErrors::IncorrectPassword;
	case static_cast<int>(CredentialErrors::Valid):
		response.text.erase(response.text.begin());
		m_sessionKey = response.text;
		return CredentialErrors::Valid;
	default:
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

	switch (resp)
	{
	case static_cast<int>(CredentialErrors::NameSize):
		return CredentialErrors::NameSize;
	case static_cast<int>(CredentialErrors::UsernameSize):
		return CredentialErrors::UsernameSize;
	case static_cast<int>(CredentialErrors::PasswordSize):
		return CredentialErrors::PasswordSize;
	case static_cast<int>(CredentialErrors::UserTaken):
		return CredentialErrors::UserTaken;
	case static_cast<int>(CredentialErrors::NameTaken):
		return CredentialErrors::NameTaken;
	case static_cast<int>(CredentialErrors::Valid):
		return CredentialErrors::Valid;

	default:
		return CredentialErrors::Other;
	}
}

bool Route::logOut()
{
	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/logOut" },
		cpr::Payload{
			{ "sessionKey", m_sessionKey}
		}
	);
	if (response.status_code == 200 || response.status_code == 202) {
		return true;
	}
	else {
		return false;
	}
}
