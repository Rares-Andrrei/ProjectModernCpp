#include "ChooseRegion.h"

ChooseRegion::ChooseRegion(QuestionManager& questions, const uint16_t& numberOfPlayers)
	:m_numberOfPlayers{numberOfPlayers}
{
	m_question = questions.randQTypeNumerical();
	std::cout << m_question;
}

void ChooseRegion::CreateOrder(const Player::Color& player, const int& playerAnswer, const int& responseTime)
{
	int differenceBetweenPlayerAnswerAndQuestionAnswer = std::abs(playerAnswer - m_question.getAnswer());

	std::tuple<int, int, Player::Color> toInsert;
	
	std::get<0>(toInsert) = differenceBetweenPlayerAnswerAndQuestionAnswer;
	std::get<1>(toInsert) = responseTime;
	std::get<2>(toInsert) = player;
	
	m_PlayerOrder.push(toInsert);
}
