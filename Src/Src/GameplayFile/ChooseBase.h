#pragma once
#include "Player.h"
#include "PlayerBase.h"
#include "../QuestionFile/QuestionManager.h"
#include "Board.h"
#include <array>
#include <queue>

class ChooseBase
{
private:
	uint16_t m_numberOfPlayers;
	QTypeNumerical m_question;
	int m_questionAnswer;

	std::priority_queue <std::pair<int, Player::Color>, std::vector<std::pair<int, Player::Color>>, std::greater<std::pair<int, Player::Color>>> m_PlayerOrder;


public:
	ChooseBase( QuestionManager& questions,uint16_t numberOfPlayers = 2);
	///selectare si afisare intrebare random
	void CreateOrder(Player::Color player, int playerAnswer);

	void setBaseZone(Board& board);

};

