#include "Database.h"
#include "Account.h"
#include "MatchInfo.h"
#include "utils.h"

bool Database::registeUser(Account account)
{
	auto unique = m_storage.get_all<Account>(sql::where(sql::c(&Account::getUsername) = account.getUsername()));
	auto unique2 = m_storage.get_all<Account>(sql::where(sql::c(&Account::getNickName) = account.getNickName()));

	if (unique.size() == 0 && unique2.size() == 0)
	{
		m_storage.replace(account);
		return true;
	}
	else
	{
		return false;
	}
}

void Database::insetMatch(MatchInfo match)
{
	m_storage.replace(match);
}

std::list<MatchInfo> Database::getMatchHistory(Account account)
{
	
	auto list1 = m_storage.get_all<MatchInfo, std::list<MatchInfo>>(sql::where(sql::c(&MatchInfo::getFirstPlace) = account.getNickName()));
	auto list2 = m_storage.get_all<MatchInfo, std::list<MatchInfo>>(sql::where(sql::c(&MatchInfo::getSecondPlace) = account.getNickName()));
	auto list3 = m_storage.get_all<MatchInfo, std::list<MatchInfo>>(sql::where(sql::c(&MatchInfo::getThirdPlace) = account.getNickName()));
	auto list4 = m_storage.get_all<MatchInfo, std::list<MatchInfo>>(sql::where(sql::c(&MatchInfo::getFourthPlace) = account.getNickName()));
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

bool Database::loginUser(Account account)
{
	if (auto user = m_storage.get_pointer<Account>(account.getUsername()))
	{
		if (user->getPassword() == account.getPassword())
		{
			return true;
		}
	}
	return false;
}

bool Database::checkUsername(std::string username)
{
	m_account.setUsername(username);
	if (auto user = m_storage.get_pointer<Account>(m_account.getUsername()))
	{
		return true;
	}
	return false;
}
