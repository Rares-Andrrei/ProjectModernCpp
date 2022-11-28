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

void ChooseBase::setBaseZone(Board& board)
{
	while (!m_PlayerOrder.empty())
	{
		std::shared_ptr<PlayerBase> player(std::make_shared < PlayerBase >(m_PlayerOrder.top().second));
		std::cout <<"Curent board format :"<< board;
		std::cout << *player <<"Player please choose a zone :";
		uint16_t index1, index2;
		std::cin >> index1 >> index2;
		board[{index1, index2}] = player;
		m_PlayerOrder.pop();
	}
}
