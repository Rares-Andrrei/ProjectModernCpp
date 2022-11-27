#pragma once
#include "Player.h"
#include "PlayerBase.h"
#include "QuestionManager.h"
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
	ChooseBase(uint16_t numberOfPlayers = 2);
	void ChooseAndPrintNumericalQuestion(QuestionManager& questions); ///selectare si afisare intrebare random
	void CreateOrder(Player::Color player, int playerAnswer);

	void setBaseZone();

};

