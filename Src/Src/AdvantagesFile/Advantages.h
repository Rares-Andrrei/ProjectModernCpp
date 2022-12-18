#pragma once
#include "AnswerSugestion.h"
#include "QTypeNumerical.h"
#include "QTypeVariants.h"
#include "AnswerFiftyFifty.h"
#include "FourCloseAnswers.h"
#include <cstdint>
#include <vector>
class Advantages
{
	QTypeVariants* m_qTypeV;
	QTypeNumerical* m_qTypeN;
	AnswerSugestion AnswerSAdvantage;

public:
	enum class Advantage : uint8_t
	{
		Fifty_Fifty,
		AnswerSugestion,
		FourCloseAnswers
	};
	Advantages();
	void getCurrentQuestion(QTypeNumerical qTypeN);
	void getCurrentQuestion(QTypeVariants qTypeV);
	int useAnswerSugestion();
	std::vector<Advantage> availableAdvantages();
	~Advantages();
};