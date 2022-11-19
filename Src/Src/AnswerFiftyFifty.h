#pragma once
#include<vector>
#include<array>
#include<string>
class AnswerFiftyFifty
{
private:
	bool m_used = false;
	std::string m_answer;
	std::vector<std::string>m_variants;
public:
	AnswerFiftyFifty(std::string answer, std::array<std::string, 4>variants);
	bool Advantage_used();
	bool get_Advantage_Fifty_Fifty();
	std::vector<std::string>Advantage_utility();
};

