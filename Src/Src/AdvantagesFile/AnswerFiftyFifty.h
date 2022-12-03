#pragma once
#include<vector>
#include<array>
#include<string>
#include "../QuestionFile/QTypeVariants.h"
class AnswerFiftyFifty
{
private:
	bool m_used = false;
	std::string m_answer;
	std::vector<std::string>m_variants;
public:
	AnswerFiftyFifty(QTypeVariants Q);
	bool AdvantageUsed();
	bool getAdvantageFiftyFifty();
	std::vector<std::string>AdvantageUtility();
};

