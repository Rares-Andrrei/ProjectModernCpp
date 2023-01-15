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
	//class CompareResponsesAndTime
	//{
	//public:
	//	bool operator()(const std::tuple<int, int, Color::ColorEnum>& p1, const std::tuple<int, int, Color::ColorEnum>& p2)
	//	{
	//		const auto& [DistFromCorrectAnswer, ResponseTime, Player] = p1;
	//		const auto& [DistFromCorrectAnswer2, ResponseTime2, Player2] = p2;
	//		return DistFromCorrectAnswer < DistFromCorrectAnswer2 || (DistFromCorrectAnswer == DistFromCorrectAnswer2 && ResponseTime < ResponseTime2);
	//	}
	//};
	std::vector <std::tuple<int, int, Color::ColorEnum>> m_PlayerOrder;

public:

	bool compareResponseAndTime(std::tuple<int, int, Color::ColorEnum> p1, std::tuple<int, int, Color::ColorEnum> p2);

	//NumericQuestionManager() = default;
	NumericQuestionManager(const uint16_t& playerNr);
	NumericQuestionManager(const QTypeNumerical& question, const uint16_t& playerNr);
	~NumericQuestionManager() = default;

	void setQuestion(const QTypeNumerical& question);
	void addPlayerResponse(int responseTime, int playerAnswer, const Color::ColorEnum& player);
	QTypeNumerical getQuestion();

	int getNumberOfEntries()const;
	std::vector<Color::ColorEnum> getPlayersOrder();
};

