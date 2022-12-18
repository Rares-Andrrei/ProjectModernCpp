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
	
}

void GameLogic::addPlayer(const std::string& firstName, const std::string& lastName)
{
	m_players.emplace_back(firstName, lastName, static_cast<Player::Color>(m_players.size()+1));
}
