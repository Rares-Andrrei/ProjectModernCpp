#include "Database.h"
#include <random>
#include "Account.h"
#include "MatchInfo.h"
#include "utils.h"

CredentialErrors Database::registerUser(const Account& account)
{
	CredentialErrors check = account.checkAccount();
	if (check != CredentialErrors::Valid)
	{
		return check;
	}
	auto uniqueUser = m_storage.get_all<Account>(sql::where(sql::c(&Account::getUsername) = account.getUsername()));
	auto uniqueName = m_storage.get_all<Account>(sql::where(sql::c(&Account::getNickName) = account.getNickName()));

	if (uniqueName.size() != 0)
	{
		return CredentialErrors::NameTaken;
	}
	if (uniqueUser.size() != 0)
	{
		return CredentialErrors::UserTaken;
	}
	m_storage.replace(account);
	return CredentialErrors::Valid;
}

void Database::insertMatch(const MatchInfo& match)
{
	m_storage.replace(match);
}

std::list<MatchInfo> Database::getMatchHistory(const Account& account)
{
	using namespace sqlite_orm;
	std::string nickname = account.getNickName();
	auto list1 = m_storage.get_all<MatchInfo, std::list<MatchInfo>>(sql::where(sql::c(&MatchInfo::getFirstPlace) == nickname));
	auto list2 = m_storage.get_all<MatchInfo, std::list<MatchInfo>>(sql::where(sql::c(&MatchInfo::getSecondPlace) == nickname));
	auto list3 = m_storage.get_all<MatchInfo, std::list<MatchInfo>>(sql::where(sql::c(&MatchInfo::getThirdPlace) == nickname));
	auto list4 = m_storage.get_all<MatchInfo, std::list<MatchInfo>>(sql::where(sql::c(&MatchInfo::getFourthPlace) == nickname));
	std::list<MatchInfo> merged;
	merged.insert(merged.end(), list1.begin(), list1.end());
	merged.insert(merged.end(), list2.begin(), list2.end());
	merged.insert(merged.end(), list3.begin(), list3.end());
	merged.insert(merged.end(), list4.begin(), list4.end());
	return merged;
}

Database::Database(const std::string& filename) : m_storage{createStorage(filename)}
{
	m_storage.sync_schema();
}

void Database::insertQTypeVariants(std::vector<QTypeVariants>& questions)
{
	using namespace sqlite_orm;
	int id = -1;
	if (auto maxId = m_storage.max(&QTypeVariants::getId))
	{
		id = *maxId;
	}
	for (QTypeVariants& q : questions)
	{
		if (!m_storage.get_all<QTypeVariants>(sql::where(sql::c(&QTypeVariants::getQuestion) == q.getQuestion())).size())
		{
			q.setId(++id);
			m_storage.replace(q);
		}
	}
}

void Database::insertQTypeNumerical(std::vector<QTypeNumerical>& questions)
{
	using namespace sqlite_orm;
	int id = -1;
	if (auto maxId = m_storage.max(&QTypeNumerical::getId))
	{
		id = *maxId;
	}
	for (QTypeNumerical& q : questions)
	{
		if (!m_storage.get_all<QTypeNumerical>(sql::where(sql::c(&QTypeNumerical::getQuestion) == q.getQuestion())).size())
		{
			q.setId(++id);
			m_storage.replace(q);
		}
	}
}

QTypeVariants Database::randQTypeVariants()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	if (auto maxId = m_storage.max(&QTypeVariants::getId))
	{
		int id = *maxId;
		std::uniform_int_distribution<> distr(0, id);
		return m_storage.get<QTypeVariants>(distr(eng));
	}
}

QTypeNumerical Database::randQTypeNumerical()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	if (auto maxId = m_storage.max(&QTypeNumerical::getId))
	{
		int id = *maxId;
		std::uniform_int_distribution<> distr(0, id);
		return m_storage.get<QTypeNumerical>(distr(eng));
	}
}


CredentialErrors Database::loginUser(Account& account)
{
	if (auto user = m_storage.get_pointer<Account>(account.getUsername()))
	{
		if (user->getPassword() == account.getPassword())
		{
			account.setNickName(user->getNickName());
			return CredentialErrors::Valid;
		}
		else
		{
			return CredentialErrors::IncorrectPassword;
		}
	}
	return CredentialErrors::IncorrectAccount;
}