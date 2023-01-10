#include "GameLogic.h"


void GameLogic::randomQTypeNumerical()
{
	m_numericQuestionManager.setQuestion(m_db->randQTypeNumerical());
}

void GameLogic::randomQTypeVariants()
{
	m_questionTypeVariants = m_db->randQTypeVariants();
}

GameLogic::GameLogic()
	:k_numberOfPlayers{ 2 }
{
}

GameLogic::GameLogic(const uint16_t& numberOfPlayers, std::shared_ptr<Database> db)
	: k_numberOfPlayers(numberOfPlayers), m_db{ db }
{
	randomQTypeNumerical();
	randomQTypeVariants();
}

bool GameLogic::checkZoneUpdates()
{
	if (m_updatedZone.has_value())
	{
		return true;
	}
	return false;
}

std::pair<int, Color::ColorEnum> GameLogic::getUpdatedZone()
{
	if (m_updatedZone.has_value())
	{
		return m_updatedZone.value();
	}
	else
	{
		return { -1, Color::ColorEnum::None };
	}
}

void GameLogic::updateZone(int zoneId, Color::ColorEnum zoneColor)
{
	if (m_board[zoneId] != m_board.end())
	{
		std::shared_ptr<Zone> newZone = std::make_shared<Zone>(zoneColor);
		m_board[zoneId] = newZone;
		m_updatedZone = { zoneId, zoneColor };
	}
}

void GameLogic::eraseUpdatedZone()
{
	if (m_updatedZone.has_value())
	{
		m_updatedZone.reset();
	}
}

crow::json::wvalue GameLogic::playersToJson(std::vector<std::shared_ptr<Player>> players)
{
	crow::json::wvalue json;
	int playerNr = 1;
	json["playerNr"] = players.size();
	for (const auto& p : players)
	{
		json["playerName" + std::to_string(playerNr)] = p->getName();
		json["playerColor" + std::to_string(playerNr)] = Color::ColorToInt(p->getColor());
		json["playerScore" + std::to_string(playerNr)] = p->getScore();
		playerNr++;
	}
	return json;
}

QTypeNumerical GameLogic::getQuestionTypeNumerical()
{
	return m_numericQuestionManager.getQuestion();
}

QTypeVariants GameLogic::getQuestionTypeVariants()
{
	return m_questionTypeVariants;
}

void GameLogic::setPlayerNumericalAnswer(int time, int response, const Color::ColorEnum& color)
{
	m_numericQuestionManager.addPlayerResponse(time, response, color);
}

bool GameLogic::NumericalAnswersReady()
{
	if (m_numericQuestionManager.getNumberOfEntries() == m_players.size())
		return true;
	return false;
}

std::vector<std::shared_ptr<Player>> GameLogic::getWinnerList()
{
	std::vector<Color::ColorEnum> order = m_numericQuestionManager.getPlayersOrder();
	std::vector<std::shared_ptr<Player>> orderedPlayers;
	
	for (const auto& c : order)
	{
		for (const auto& player : m_players)
		{
			if (player->getColor() == c)
			{
				orderedPlayers.push_back(player);
			}
		}
	}
	randomQTypeNumerical();
	eraseUpdatedZone();
	return orderedPlayers;
}

void GameLogic::StartGame()
{
	if (m_players.size() != k_numberOfPlayers)
	{
		std::cout << "Not enough players to start the game" << std::endl;
		return;
	}
	m_board = Board(k_numberOfPlayers);
	m_questions.addQFiles("QTypeVariants.txt", "QTypeNumerical.txt");
	chooseBasePhase();
	chooseRegionsPhase();
	duelsPhase();
}

void GameLogic::EndGame()
{
	m_board.ObtainTotalScore();
}

void GameLogic::chooseBasePhase()
{
	ChooseBase chooseBase(m_questions);
	int playerAnswer;
	for (uint16_t index = 0; index < m_players.size(); index++)
	{
		std::cout << Color::ColorToString(m_players[index]->getColor()) << " player answer: ";
		std::cin >> playerAnswer;
		chooseBase.CreateOrder(m_players[index]->getColor(), 0, playerAnswer);
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
			std::cout << Color::ColorToString(m_players[index]->getColor()) << " player answer: ";
			std::cin >> playerAnswer;
			chooseRegion.CreateOrder(m_players[index]->getColor(), 0, playerAnswer);
		}

		chooseRegion.setRegionZone(m_board);
	}
}
// 0 0 0 0 0 1 1 1 1 1 1 2 0 2 1 1 1 0 2 1 2 2 0 0 2 0
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
			std::cout << std::endl << m_board << std::endl;
			std::cout << Color::ColorToString(player->getColor()) << " Choose a zone to Attack : ";
			Board::Position position;
			auto& [row, column] = position;
			while (true)
			{
				try
				{
					std::cin >> row >> column;
					if (m_board[position]->getColor() == Color::ColorEnum::None)
					{
						throw std::out_of_range("Board Index Out of range , Please choose another position: ");
					}
					if (m_board[position]->getColor() != player->getColor())
						break;
					else {
						throw std::logic_error("You can't attack your own zone , Please choose another position: ");
					}
				}
				catch (const std::exception& e)
				{
					std::cout << std::endl << e.what() << std::endl;
				}

			}
			Duel duel(player->getColor(), m_board[position]);
			duel.generateQuestion(m_questions);
			duel.startDuel();
			auto isBase = std::dynamic_pointer_cast<PlayerBase>(m_board[position]);
			if (isBase && checkIfPlayerWasEliminated(isBase))
			{
				for (uint16_t ind = 0; ind < m_players.size(); ind++)
				{
					if (m_players[ind]->getColor() == player->getColor())
					{
						m_eliminatedPlayers.emplace_back(m_players[ind]);
						m_board.eliminatePlayer(m_players[ind]->getColor(), player->getColor());
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

void GameLogic::addPlayer(std::shared_ptr<Player> player)
{
	m_players.push_back(player);
}
