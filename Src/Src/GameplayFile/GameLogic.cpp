#include "GameLogic.h"
#include <random>
#include <algorithm>

void GameLogic::randomQTypeNumerical()
{
	m_numericQuestionManager.setQuestion(m_db->randQTypeNumerical());
}

void GameLogic::setDuel(Color::ColorEnum attacker, int regionId)
{
	if (m_board[regionId] != m_board.end())
	{
		m_duel = Duel(attacker, m_board[regionId], regionId, m_db);
	}
}

void GameLogic::getDuelingPlayersAndZone(Color::ColorEnum& c1, Color::ColorEnum& c2, int& zoneId)
{
	m_duel->getDuelInfo(c1, c2, zoneId);
}

void GameLogic::createDuelOrder()
{
	std::vector<Color::ColorEnum> playerOrder;
	const uint8_t nrOfDuelsPerPlayer = 3;
	for (auto player : m_players)
	{
		std::fill_n(std::back_inserter(playerOrder), nrOfDuelsPerPlayer, player->getColor());
	}
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(playerOrder.begin(), playerOrder.end(), g);
	for (auto color : playerOrder)
	{
		m_duelOrder.push(color);
	}
}

int GameLogic::getDuelZoneId()
{
	return m_duel->getZoneId();
}

int GameLogic::getZoneId(std::shared_ptr<Zone> zone)
{
	int id = 0;
	while (m_board[id] != m_board.end())
	{
		if (zone == m_board[id])
		{
			return id;
		}
		id++;
	}
	return -1;
}

void GameLogic::duelPlayerResponse(Color::ColorEnum color, int variant)
{
	m_duel->setDuelVaraintsAnswer(color, variant);
}

void GameLogic::setColorToAttack()
{
	if (m_duelOrder.size() != 0)
	{
		m_colorToAttack = m_duelOrder.front();
	}
	else
	{
		m_colorToAttack = Color::ColorEnum::None;
	}
}

void GameLogic::setDuelNumericalAnswer(int time, int response, const Color::ColorEnum& color)
{
	m_duel->setNumericalAnswer(time, response, color);
}

Color::ColorEnum GameLogic::currentDuelAttacker()
{
	return m_duel->getAttacker();
}

QTypeNumerical GameLogic::getDuelNumericalQ()
{
	return m_duel->getQTypeNumerical();
}

void GameLogic::deleteColorToAttack()
{
	m_duelOrder.pop();
}

std::vector<std::shared_ptr<Zone>> GameLogic::getDuelZones()
{
	return m_duel->getUpdatedZones();
}

Duel::DuelState GameLogic::getDuelState()
{
	return m_duel->getState();
}

void GameLogic::setDuelPlayerWinner()
{
	m_duel->setWinner(m_board);
}

bool GameLogic::duelDraw()
{
	if (m_duel.has_value())
	{
		return m_duel->isDraw();
	}
	else
	{
		return false;
	}
}

Color::ColorEnum GameLogic::getAttackerColor()
{
	return m_duelOrder.front();
}

std::pair<int, int> GameLogic::taxForAdvantage(Color::ColorEnum color)
{
	int id = 0;
	while (m_board[id] != m_board.end())
	{
		if (m_board[id]->getScore() >= 200 && m_board[id]->getColor() == color)
		{
			m_board[id]->DecrementScore();
			return std::make_pair(id, m_board[id]->getScore());
			break;
		}
		id++;
	}
}

void GameLogic::addWaitingRequest(const Color::ColorEnum& color)
{
	m_requests[color] = true;
}

bool GameLogic::allRequestsReady()
{
	bool allReady = true;
	for (auto request : m_requests)
	{
		if (!request.second)
		{
			allReady = false;
			break;
		}
	}
	return allReady;
}

void GameLogic::deleteRequestsReady()
{
	for (auto request : m_requests)
	{
		m_requests[request.first] = false;
	}
}

bool GameLogic::ValidateBasePosition(int idZone)
{
	return m_board.ValidateBasePosition(idZone);
}

bool GameLogic::ValidateRegionPosition(int idZone, const Color::ColorEnum& color)
{
	return m_board.ValidateRegionPosition(idZone, color);
}

bool GameLogic::ValidateAttackMove(int idZone, const Color::ColorEnum& color)
{
	return m_board.ValidateAttackMove(idZone, color);
}

GameLogic::GameLogic()
	:k_numberOfPlayers{ 2 }, m_numericQuestionManager{ NumericQuestionManager(k_numberOfPlayers) }
{
	randomQTypeNumerical();
}

GameLogic::GameLogic(const uint16_t& numberOfPlayers, std::shared_ptr<Database> db)
	: k_numberOfPlayers(numberOfPlayers), m_db{ db }, m_numericQuestionManager{ NumericQuestionManager(numberOfPlayers) } , m_board(numberOfPlayers)
{
	randomQTypeNumerical();
}

bool GameLogic::checkZoneUpdates()
{
	if (m_updatedZone.has_value())
	{
		return true;
	}
	return false;
}

bool GameLogic::CheckIfBoardIsFull()
{
	return m_board.CheckIfBoardIsFull();
}

bool GameLogic::checkIfPlayerCanUseAdvantages(const Color::ColorEnum& color)
{
	return m_board.checkIfPlayerCanUseAdvantages(color);
}

std::tuple<int, Color::ColorEnum, int, int> GameLogic::getZoneInfo(int idZone)
{
	return m_board.getZoneInfo(idZone);
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
	if (m_board[zoneId] == nullptr && m_board[zoneId] != m_board.end())
	{

		for (auto& player : m_players)
		{
			if (player->getColor() != zoneColor)
			{
				continue;
			}
			m_board.incrementModifiedZones();
			if (m_board.getModifiedZones() > m_board.getNumberOfPlayers())
			{
				std::shared_ptr<Zone> newZone = std::make_shared<Zone>(zoneColor);
				player->setScore(player->getScore() + 100);
				m_board[zoneId] = newZone;
				m_updatedZone = { zoneId, zoneColor };
			}
			else
			{
				std::shared_ptr<PlayerBase> newBase = std::make_shared<PlayerBase>(zoneColor);
				player->setScore(300);
				m_board[zoneId] = newBase;
				m_updatedZone = { zoneId, zoneColor };
			}
			break;
		}
		m_board.generateNeighbours();
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
	return m_duel->getQTypeVariants();
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
	return orderedPlayers;
}

std::vector<std::shared_ptr<Player>> GameLogic::getPlayers()
{
	return m_players;
}

//void GameLogic::StartGame()
//{
//	if (m_players.size() != k_numberOfPlayers)
//	{
//		std::cout << "Not enough players to start the game" << std::endl;
//		return;
//	}
//	m_board = Board(k_numberOfPlayers);
//	m_questions.addQFiles("QTypeVariants.txt", "QTypeNumerical.txt");
//	chooseBasePhase();
//	chooseRegionsPhase();
//	duelsPhase();
//}

void GameLogic::EndGame()
{
	m_board.ObtainTotalScore();
}

//void GameLogic::chooseBasePhase()
//{
//	ChooseBase chooseBase(m_questions);
//	int playerAnswer;
//	for (uint16_t index = 0; index < m_players.size(); index++)
//	{
//		std::cout << Color::ColorToString(m_players[index]->getColor()) << " player answer: ";
//		std::cin >> playerAnswer;
//		chooseBase.CreateOrder(m_players[index]->getColor(), 0, playerAnswer);
//	}
//
//	chooseBase.setBaseZone(m_board);
//}

//void GameLogic::chooseRegionsPhase()
//{
//	uint16_t roundCounter = 0;
//
//	while (m_board.CheckIfBoardIsFull() == false)
//	{
//		int playerAnswer;
//		ChooseRegion chooseRegion(m_questions);
//
//		for (uint16_t index = 0; index < m_players.size(); index++)
//		{
//			std::cout << Color::ColorToString(m_players[index]->getColor()) << " player answer: ";
//			std::cin >> playerAnswer;
//			chooseRegion.CreateOrder(m_players[index]->getColor(), 0, playerAnswer);
//		}
//
//		chooseRegion.setRegionZone(m_board);
//	}
//}
// 0 0 0 0 0 1 1 1 1 1 1 2 0 2 1 1 1 0 2 1 2 2 0 0 2 0
//void GameLogic::duelsPhase()
//{
//	uint16_t maxRounds = 5;
//	uint16_t roundCounter = 0;
//	if (k_numberOfPlayers == 2)
//		maxRounds = 4;
//	while (roundCounter < maxRounds)
//	{
//		roundCounter++;
//		for (const auto& player : m_players)
//		{
//			std::cout << std::endl << m_board << std::endl;
//			std::cout << Color::ColorToString(player->getColor()) << " Choose a zone to Attack : ";
//			Board::Position position;
//			auto& [row, column] = position;
//			while (true)
//			{
//				try
//				{
//					std::cin >> row >> column;
//					if (m_board[position]->getColor() == Color::ColorEnum::None)
//					{
//						throw std::out_of_range("Board Index Out of range , Please choose another position: ");
//					}
//					if (m_board[position]->getColor() != player->getColor())
//						break;
//					else {
//						throw std::logic_error("You can't attack your own zone , Please choose another position: ");
//					}
//				}
//				catch (const std::exception& e)
//				{
//					std::cout << std::endl << e.what() << std::endl;
//				}
//
//			}
//			Duel duel(player->getColor(), m_board[position]);
//			duel.generateQuestion(m_questions);
//			duel.startDuel();
//			auto isBase = std::dynamic_pointer_cast<PlayerBase>(m_board[position]);
//			if (isBase && checkIfPlayerWasEliminated(isBase))
//			{
//				for (uint16_t ind = 0; ind < m_players.size(); ind++)
//				{
//					if (m_players[ind]->getColor() == player->getColor())
//					{
//						m_eliminatedPlayers.emplace_back(m_players[ind]);
//						m_board.eliminatePlayer(m_players[ind]->getColor(), player->getColor());
//						m_players.erase(m_players.begin() + ind);
//						break;
//					}
//				}
//			}
//		}
//	}
//}

bool GameLogic::checkIfPlayerWasEliminated(std::shared_ptr<PlayerBase>& playerBase)
{
	return playerBase->getNumberOfLifesLeft() == 0;
}

void GameLogic::updatePlayersScores()
{
	for (auto& player : m_players)
	{
		player->setScore(m_board.getPlayerScore(player->getColor()));
	}
}

void GameLogic::addPlayer(std::shared_ptr<Player> player)
{
	m_players.push_back(player);
}
