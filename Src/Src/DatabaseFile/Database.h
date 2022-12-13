#pragma once
#include <list>
#include <sqlite_orm/sqlite_orm.h>
#include "MatchInfo.h"
#include "Account.h"
namespace sql = sqlite_orm;

inline auto createStorage(const std::string& filename)
{
	return sql::make_storage(filename,
		sql::make_table(
			"Account",
			sql::make_column("Username", &Account::getUsername, &Account::setUsername, sql::primary_key()),
			sql::make_column("Password", &Account::getPassword, &Account::setPassword),
			sql::make_column("NickName", &Account::getNickName, &Account::setNickName)
		),
			sql::make_table(
				"MatchInfo",
				sql::make_column("Date", &MatchInfo::getDate, &MatchInfo::setDate),
				sql::make_column("FirstPlace", &MatchInfo::getFirstPlace, &MatchInfo::setFirstPlace),
				sql::make_column("SecondPlace", &MatchInfo::getSecondPlace, &MatchInfo::setSecondPlace),
				sql::make_column("ThirdPlace", &MatchInfo::getThirdPlace, &MatchInfo::setThirdPlace),
				sql::make_column("FourthPlace", &MatchInfo::getFourthPlace, &MatchInfo::setFourthPlace)
			)
	);
}
using Storage = decltype(createStorage(""));

class Database
{
	Storage m_storage;
	Account m_account;

public:
	Database(const std::string& filename);
	bool loginUser(Account account);
	bool checkUsername(std::string username);
	bool registeUser(Account account);
	void insetMatch(MatchInfo match);
	std::list<MatchInfo> getMatchHistory(Account account);
};