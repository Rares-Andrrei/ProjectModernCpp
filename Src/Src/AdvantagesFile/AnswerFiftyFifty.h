#pragma once
#include<vector>
#include<array>
#include<string>
#include "../QuestionFile/QTypeVariants.h"
#include<random>

class AnswerFiftyFifty
{
private:
	std::string m_answer;
	std::vector<std::string>m_variants;
public:
	AnswerFiftyFifty(QTypeVariants& Q);
	std::array<std::string, 2>AdvantageUtility();
};