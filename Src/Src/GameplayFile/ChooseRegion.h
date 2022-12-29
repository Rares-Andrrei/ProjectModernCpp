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
	QTypeNumerical m_question;
	int m_questionAnswer;

	class CompareResponsesAndTime
	{
	public:
		bool operator()(const std::tuple<int, int, Color::ColorEnum>& p1, const std::tuple<int, int, Color::ColorEnum>& p2)
		{
			const auto& [DistFromCorrectAnswer, ResponseTime, Player] = p1;
			const auto& [DistFromCorrectAnswer2, ResponseTime2, Player2] = p2;
			return DistFromCorrectAnswer < DistFromCorrectAnswer2 || (DistFromCorrectAnswer == DistFromCorrectAnswer2 && ResponseTime < ResponseTime2);
		}
	};
	std::priority_queue <std::tuple<int, int, Color::ColorEnum>, std::vector<std::tuple<int, int, Color::ColorEnum>>, CompareResponsesAndTime> m_PlayerOrder;

public:
	ChooseRegion(QuestionManager& questions);

	void CreateOrder(const Color::ColorEnum& player, const  int& playerAnswer, const int& responseTime);

	void setRegionZone(Board& board);

};

