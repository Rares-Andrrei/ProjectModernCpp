#pragma once
#include "Player.h"
#include <array>
#include <string>
#include <optional>

class MatchInfo
{
	std::string m_date;
	std::array<std::optional<std::string>, 4> m_ranking;
public:
	static std::string getEndtime();
	MatchInfo() = default;
	MatchInfo(std::string date, std::array<std::optional<std::string>, 4> ranking);
	std::string getDate() const;
	void setDate(std::string date);
	std::string getFirstPlace() const;
	void setFirstPlace(const std::string& nickname);
	std::string getSecondPlace() const;
	void setSecondPlace(const std::string& nickname);
	std::string getThirdPlace() const;
	void setThirdPlace(const std::string& nickname);
	std::string getFourthPlace() const;
	void setFourthPlace(const std::string& nickname);
};