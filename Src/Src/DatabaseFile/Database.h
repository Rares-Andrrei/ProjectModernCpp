#pragma once
#include <list>
#include "CredentialErrors.h"
#include <sqlite_orm/sqlite_orm.h>
#include "MatchInfo.h"
#include "Account.h"
#include "QTypeVariants.h"
#include "QTypeNumerical.h"

namespace sql = sqlite_orm;

inline auto createStorage(const std::string& filename)
{
	return sql::make_storage(filename,
		sql::make_table(
			"Account",
			sql::make_column("Username", &Account::getUsername, &Account::setUsername, sql::primary_key()),
			sql::make_column("Password", &Account::getPassword, &Account::setPassword),
			sql::make_column("NickName", &Account::getNickName, &Account::setNickName, sql::unique())
		),
		sql::make_table(
			"MatchInfo",
			sql::make_column("Date", &MatchInfo::getDate, &MatchInfo::setDate),
			sql::make_column("FirstPlace", &MatchInfo::getFirstPlace, &MatchInfo::setFirstPlace),
			sql::make_column("SecondPlace", &MatchInfo::getSecondPlace, &MatchInfo::setSecondPlace),
			sql::make_column("ThirdPlace", &MatchInfo::getThirdPlace, &MatchInfo::setThirdPlace),
			sql::make_column("FourthPlace", &MatchInfo::getFourthPlace, &MatchInfo::setFourthPlace)
		),
		sql::make_table("QuestionsTypeVaraints",
			sql::make_column("Id", &QTypeVariants::getId, &QTypeVariants::setId, sql::primary_key()),
			sql::make_column("Question", &QTypeVariants::getQuestion, &QTypeVariants::setQuestion, sql::unique()),
			sql::make_column("Var1", &QTypeVariants::getVariant<0>, &QTypeVariants::setVariant<0>),
			sql::make_column("Var2", &QTypeVariants::getVariant<1>, &QTypeVariants::setVariant<1>),
			sql::make_column("Var3", &QTypeVariants::getVariant<2>, &QTypeVariants::setVariant<2>),
			sql::make_column("Var4", &QTypeVariants::getVariant<3>, &QTypeVariants::setVariant<3>),
			sql::make_column("Answer", &QTypeVariants::getAnswer, &QTypeVariants::setAnswer)
		),
		sql::make_table("QuestionsTypeNumerical",
			sql::make_column("Id", &QTypeNumerical::getId, &QTypeNumerical::setId, sql::primary_key()),
			sql::make_column("Question", &QTypeNumerical::getQuestion, &QTypeNumerical::setQuestion, sql::unique()),
			sql::make_column("Answer", &QTypeNumerical::getAnswer, &QTypeNumerical::setAnswer)
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
	void insertQTypeVariants(std::vector<QTypeVariants>& questions);
	void insertQTypeNumerical(std::vector<QTypeNumerical>& questions);
	QTypeVariants randQTypeVariants();
	QTypeNumerical randQTypeNumerical();

	CredentialErrors loginUser(Account& account);

	CredentialErrors registerUser(const Account& account);

	void insertMatch(const MatchInfo& match);
	std::list<MatchInfo> getMatchHistory(const std::string& account);
};