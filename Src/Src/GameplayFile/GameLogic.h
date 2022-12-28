#pragma once
#include "Board.h"
#include "QuestionManager.h"
#include "Player.h"
#include  "Advantages.h"
#include "ChooseBase.h"
#include "Duel.h"

class GameLogic
{
	Board m_board;
	QuestionManager m_questions;
	const uint16_t k_numberOfPlayers;
	std::vector<Player> m_players;
	std::vector<Player> m_eliminatedPlayers;
	//std::vector<std::shared_ptr<Advantages>> m_advantages; // de vazut unde sa fie folosit . 

public:
	GameLogic();
	GameLogic(const uint16_t& numberOfPlayers);
	//GameLogic(const GameLogic&) = delete;
	//GameLogic(GameLogic&&) = delete;
	//GameLogic& operator=(const GameLogic&) = delete;
	//GameLogic& operator=(GameLogic&&) = delete;

	void StartGame();
	void EndGame();
	void addPlayer(const std::string& name);

	~GameLogic() = default;
private:

	void phases();
	void chooseBasePhase();
	void chooseRegionsPhase();
	void duelsPhase();
	bool checkIfPlayerWasEliminated(std::shared_ptr<PlayerBase>& playerBase);
};

