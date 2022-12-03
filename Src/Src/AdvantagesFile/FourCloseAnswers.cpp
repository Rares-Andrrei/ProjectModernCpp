#include "FourCloseAnswers.h"
#include <random>

void FourCloseAnswers::GenerateVariants(QTypeNumerical q)
{
	int correctAnswer = q.getAnswer();

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, m_answers.size() - 1);
	int rando = distr(eng);

	int answer10 = correctAnswer - (correctAnswer * 0.10);
	int answer50 = correctAnswer + (correctAnswer * 0.50);
	int answer75 = correctAnswer - (correctAnswer * 0.75);

	bool a10 = false;
	bool a50 = false;
	bool a75 = false;

	for (int i = 0; i < m_answers.size(); i++)
	{
		if (i == rando)
		{
			m_answers[i] = correctAnswer;
		}
		else
			if (m_answers[i])
			{
				if (a10 == false)
				{
					m_answers[i] = answer10;
					a10 = true;
				}
				else
					if (a50 == false)
					{
						m_answers[i] = answer50;
						a50 = true;
					}
					else
					{
						if (a75 == false)
						{
							m_answers[i] = answer75;
							a75 = true;
						}
					}
			}
	}
}

bool FourCloseAnswers::AdvantageIsUsed()
{
	if (m_used == false)
		return false;
	return true;
}

std::ostream& operator<<(std::ostream& out, FourCloseAnswers const& answers)
{
	for (auto& a : answers.m_answers)
	{
		out << a << " ";
	}
	out << std::endl;
	return out;
}
