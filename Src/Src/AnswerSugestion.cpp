#include "AnswerSugestion.h"
#include <random>

AnswerSugestion::AnswerSugestion() : m_used{ false } {}

int AnswerSugestion::useAdvantage(int answer)
{
	const uint8_t eroare = 6;
	if (!m_used)
	{
		m_used = true;
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> distr(0, eroare);
		return answer + (distr(eng) * answer / 100);
	}
	else
	{
		//throw exception
	}
}

bool AnswerSugestion::isUsed()
{
	return m_used;
}
