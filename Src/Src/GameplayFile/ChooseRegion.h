#pragma once
#include <cstdlib>
#include "Player.h"
#include "PlayerBase.h"
#include "QuestionManager.h"
#include "Board.h"
#include <array>
#include <queue>

class ChooseRegion
{
protected:
	uint16_t m_numberOfPlayers;
	QTypeNumerical m_question;
	int m_questionAnswer;

	std::priority_queue <std::tuple<int, int, Player::Color>, std::vector<std::tuple<int, int, Player::Color>>, CompareResponsesAndTime> m_PlayerOrder;


public:
	ChooseRegion(QuestionManager& questions, const  uint16_t& numberOfPlayers);

	void CreateOrder(const Player::Color& player, const  int& playerAnswer, const int& responseTime);

	void setBaseZone(Board& board);

};

