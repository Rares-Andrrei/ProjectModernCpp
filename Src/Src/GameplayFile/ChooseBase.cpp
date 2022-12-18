#include "ChooseBase.h"

ChooseBase::ChooseBase(QuestionManager& questions/*, const uint16_t& numberOfPlayers*/)
	:ChooseRegion(questions/*, numberOfPlayers*/)
{

}

void ChooseBase::setBaseZone(Board& board)
{
	while (!m_PlayerOrder.empty())
	{
		try
		{
			auto& [DistFromCorrectAnswer, ResponseTime, Player] = m_PlayerOrder.top();

			std::shared_ptr<PlayerBase> player(std::make_shared < PlayerBase >(Player));
			//std::cout << "Curent board format :" << board;
			std::cout << *player << "Player please choose a zone :";

			uint16_t index1, index2;
			uint16_t numPlayers = board.getNumberOfPlayers();
			std::cin >> index1 >> index2;
			std::string message = "Invalid parameters";
			board[{index1, index2}] = player;
			m_PlayerOrder.pop();
		}
		catch (const std::exception& ex)
		{
			//std::cout << std::endl;
			std::cout << ex.what();
			std::cout << std::endl;
		}
	}
}
