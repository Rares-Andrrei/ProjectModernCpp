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
	
void GameLogic::chooseBasePhase()
{
	ChooseBase chooseBase(m_questions);
	int playerAnswer;
	for (uint16_t index = 0; index < m_players.size(); index++)
	{
		std::cout << Player::ColorToString(m_players[index].getColor()) << " player answer: ";
		std::cin >> playerAnswer;
		chooseBase.CreateOrder(m_players[index].getColor(), 0, playerAnswer);
	}

	chooseBase.setBaseZone(m_board);
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

void GameLogic::duelsPhase()
{
	uint16_t maxRounds = 5;
	uint16_t roundCounter = 0;
	if (k_numberOfPlayers == 2)
		maxRounds = 4;
	while (roundCounter < maxRounds)
	{
		roundCounter++;
		for (const auto& player : m_players)
		{
			std::cout << m_board<<std::endl;
			std::cout << Player::ColorToString(player.getColor()) << " Choose a zone to Attack : ";
			Board::Position position;
			auto& [row, column] = position;
			while (true)
			{
				std::cin >> row >> column;
				if (m_board[position]->getColor() != player.getColor())
					break;
				else {
					std::cout << "You can't attack your own zone, please choose another one : ";
				}
			}
			Duel duel(player.getColor(), m_board[position]);
			duel.generateQuestion(m_questions);
			duel.startDuel();
			auto isBase = std::dynamic_pointer_cast<PlayerBase>(m_board[position]);
			if (isBase && checkIfPlayerWasEliminated(isBase))
			{
				for (uint16_t ind = 0; ind < m_players.size(); ind++)
				{
					if (m_players[ind].getColor() == player.getColor())
					{
						m_eliminatedPlayers.emplace_back(m_players[ind]);
						m_board.eliminatePlayer(m_players[ind].getColor(), player.getColor());
						m_players.erase(m_players.begin() + ind);
						break;
					}
				}
			}
		}
	}
}

bool GameLogic::checkIfPlayerWasEliminated(std::shared_ptr<PlayerBase>& playerBase)
{
	return playerBase->getNumberOfLifesLeft() == 0;
}

void GameLogic::addPlayer(const std::string& firstName, const std::string& lastName)
{
	m_players.emplace_back(firstName, lastName, static_cast<Player::Color>(m_players.size() + 1));
}
