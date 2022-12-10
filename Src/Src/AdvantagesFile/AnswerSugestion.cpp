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
		std::string message = "The advantage is already use";
		try
		{
			if (m_used = true)
			{
				throw(message);
			}
		}
		catch (std::string message)
		{
			std::cerr << "Pay attention" << message;
		}
	}
}


bool AnswerSugestion::isUsed()
{
	return m_used;
}
