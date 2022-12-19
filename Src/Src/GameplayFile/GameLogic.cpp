#include "GameLogic.h"


GameLogic::GameLogic(const uint16_t& numberOfPlayers)
	: k_numberOfPlayers(numberOfPlayers)
{
}

void GameLogic::StartGame()
{
	if (m_players.size() != k_numberOfPlayers)
	{
		std::cout << "Not enough players to start the game" << std::endl;
		return;
	}
	
void GameLogic::chooseRegionsPhase()
{
	uint16_t roundCounter = 0;

	while (m_board.CheckIfBoardIsFull() == false)
	{
		int playerAnswer;
		ChooseRegion chooseRegion(m_questions);

		for (uint16_t index = 0; index < m_players.size(); index++)
		{
			std::cout << Player::ColorToString(m_players[index].getColor()) << " player answer: ";
			std::cin >> playerAnswer;
			chooseRegion.CreateOrder(m_players[index].getColor(), 0, playerAnswer);
		}

		chooseRegion.setRegionZone(m_board);
	}
}
}

void GameLogic::addPlayer(const std::string& firstName, const std::string& lastName)
{
	m_players.emplace_back(firstName, lastName, static_cast<Player::Color>(m_players.size()+1));
}
