#include <cstdlib>
#include "../../Player/Player/Player.h"
#include "PlayerBase.h"
#include "QuestionManager.h"
#include "Board.h"
#include <array>
#include <queue>

class NumericQuestionManager
{
	QTypeNumerical m_question;

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
	NumericQuestionManager() = default;
	NumericQuestionManager(const QTypeNumerical& question);
	~NumericQuestionManager() = default;

	void setQuestion(const QTypeNumerical& question);
	void addPlayerResponse(const int& responseTime, const int& playerAnswer, const Color::ColorEnum& player);
	QTypeNumerical getQuestion();

	int getNumberOfEntries()const;
	std::vector<Color::ColorEnum> getPlayersOrder();
};

