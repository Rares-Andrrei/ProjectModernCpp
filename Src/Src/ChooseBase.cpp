#include "ChooseBase.h"

ChooseBase::ChooseBase(uint16_t numberOfPlayers)
	:m_numberOfPlayers{ numberOfPlayers }
{
}

void ChooseBase::ChooseAndPrintNumericalQuestion(QuestionManager& questions)
{
	m_question = questions.randQTypeNumerical();
	std::cout << m_question;
}

void ChooseBase::CreateOrder(Player::Color player, int playerAnswer)
{
	int differenceBetweenPlayerAnswerAndQuestionAnswer = std::abs(playerAnswer - m_question.getAnswer());

	std::pair<int, Player::Color> toInsert;
	toInsert.first = differenceBetweenPlayerAnswerAndQuestionAnswer;
	toInsert.second = player;
	m_PlayerOrder.push(toInsert);
}

void ChooseBase::setBaseZone()
{
	while (!m_PlayerOrder.empty())
	{
		PlayerBase player(m_PlayerOrder.top().second);
		std::cout << player;
		m_PlayerOrder.pop();
	}
}
