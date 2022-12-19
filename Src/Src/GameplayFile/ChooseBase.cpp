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
			std::cout << board << std::endl;
			std::shared_ptr<PlayerBase> player(std::make_shared < PlayerBase >(Player));
			//std::cout << "Curent board format :" << board;
			std::cout << *player << "Player please choose a zone :";
			
			Board::Position position;
			auto& [row, column] = position;
			std::cin >> row >> column;
			if (board[position] == nullptr)
			{
				board[position] = player;
				m_PlayerOrder.pop();
				continue;
			}
			throw std::invalid_argument("This zone is already taken or is invalid");
		}
		catch (const std::exception& ex)
		{
			//std::cout << std::endl;
			std::cout <<std::endl<< ex.what()<<std::endl;
		}
	}
}
