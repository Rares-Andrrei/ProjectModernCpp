#pragma once
#include <cstdlib>
#include "../../Player/Player/Player.h"
#include "PlayerBase.h"
#include "QuestionManager.h"
#include "Board.h"
#include <array>
#include <queue>
#include <algorithm>
#include <vector>

class NumericQuestionManager
{
	QTypeNumerical m_question;
	uint16_t m_playerNr;
	std::vector <std::tuple<int, int, Color::ColorEnum>> m_PlayerOrder;

public:

	bool compareResponseAndTime(std::tuple<int, int, Color::ColorEnum> p1, std::tuple<int, int, Color::ColorEnum> p2);

	NumericQuestionManager(const uint16_t& playerNr);
	NumericQuestionManager(const QTypeNumerical& question, const uint16_t& playerNr);
	~NumericQuestionManager() = default;

	void setQuestion(const QTypeNumerical& question);
	void addPlayerResponse(int responseTime, int playerAnswer, const Color::ColorEnum& player);
	QTypeNumerical getQuestion();

	int getNumberOfEntries()const;
	std::vector<Color::ColorEnum> getPlayersOrder();
};

