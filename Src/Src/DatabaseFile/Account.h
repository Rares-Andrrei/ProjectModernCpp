#pragma once
#include "CredentialErrors.h"
#include <string>
#include <optional>
class Account
{
	std::string m_username;
	std::string m_password;
	std::optional<std::string> m_nickName;
public:
	Account() = default;
	Account(const std::string& username, const std::string& password, const std::string& nickname);
	std::string getUsername() const;
	std::string getPassword() const;
	std::string getNickName() const;
	void setUsername(const std::string& username);
	void setPassword(const std::string& password);
	void setNickName(const std::string& nickName); 
	CredentialErrors checkAccount() const;
};



