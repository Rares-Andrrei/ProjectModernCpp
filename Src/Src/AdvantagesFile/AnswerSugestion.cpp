#include "AnswerSugestion.h"
#include <random>

AnswerSugestion::AnswerSugestion()
{}

int AnswerSugestion::useAdvantage(int answer)
{
	const uint8_t eroare = 6;
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, eroare);
	return answer + (distr(eng) * answer / 100);
}