#include "ChooseRegion.h"

ChooseRegion::ChooseRegion(QuestionManager& questions)
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

void ChooseRegion::setRegionZone(Board& board)
{
	bool twoPlayersGame = false;
	if (m_PlayerOrder.size() == 2)
		twoPlayersGame = true;
	while (!m_PlayerOrder.empty())
	{
		auto& [DistFromCorrectAnswer, ResponseTime, Player] = m_PlayerOrder.top();
		int regionsLeftToTake = m_PlayerOrder.size();
		if (twoPlayersGame == false)
			regionsLeftToTake--;

		while (regionsLeftToTake > 0 && !board.CheckIfBoardIsFull())
		{
			try
			{
				std::shared_ptr<Zone> player(std::make_shared < Zone >(Player));
				std::cout << "Curent board format :" << board;
				std::cout << *player << "Player please choose a zone :";

				uint16_t index1, index2;
				uint16_t numPlayers = board.getNumberOfPlayers();
				std::cin >> index1 >> index2;
				std::string message = "Invalid parameters";
				board[{index1, index2}] = player;
				regionsLeftToTake--;
			}
			catch (const std::exception& ex)
			{
				//std::cout << std::endl;
				std::cout << ex.what();
				std::cout << std::endl;
			}
		}
		m_PlayerOrder.pop();
	}
}
