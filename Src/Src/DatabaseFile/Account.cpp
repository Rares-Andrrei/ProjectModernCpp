#include "Account.h"

Account::Account(const std::string& username, const std::string& password, const std::string& nickname) : m_username{ username }, m_password{ password }, m_nickName{ nickname }
{}

std::string Account::getUsername() const
{
	return m_username;
}

std::string Account::getPassword() const
{
	return m_password;
}

std::string Account::getNickName() const
{
	return m_nickName.value();
}

void Account::setUsername(const std::string& username)
{
	this->m_username = username;
}

void Account::setPassword(const std::string& password)
{
	this->m_password = password;
}

void Account::setNickName(const std::string& nickName)
{
	this->m_nickName = nickName;
}

CredentialErrors Account::checkAccount() const
{
	if (m_nickName.has_value())
	{
		if (m_nickName.value().size() < 4)
		{
			return CredentialErrors::NameSize;
		}
	}
	if (m_username.size() < 6)
	{
		return CredentialErrors::UsernameSize;
	}
	if (m_password.size() < 6)
	{
		return CredentialErrors::PasswordSize;
	}

	return CredentialErrors::Valid;
}