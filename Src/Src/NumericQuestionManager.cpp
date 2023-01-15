#include "NumericQuestionManager.h"

bool NumericQuestionManager::compareResponseAndTime(std::tuple<int, int, Color::ColorEnum> p1, std::tuple<int, int, Color::ColorEnum> p2)
{
	const auto& [DistFromCorrectAnswer, ResponseTime, Player] = p1;
	const auto& [DistFromCorrectAnswer2, ResponseTime2, Player2] = p2;
	if (DistFromCorrectAnswer < DistFromCorrectAnswer2)
		return true;
	if (DistFromCorrectAnswer == DistFromCorrectAnswer2 && ResponseTime < ResponseTime2)
		return true;
	return false;
}

NumericQuestionManager::NumericQuestionManager(const uint16_t& playerNr) : m_playerNr{ playerNr }
{
}

NumericQuestionManager::NumericQuestionManager(const QTypeNumerical& question, const uint16_t& playerNr)
	: m_question{ question }, m_playerNr{ playerNr }
{
}

void NumericQuestionManager::setQuestion(const QTypeNumerical& question)
{
	m_question = question;
}

void NumericQuestionManager::addPlayerResponse(int responseTime, int playerAnswer, const Color::ColorEnum& player)
{
	int value = abs(m_question.getAnswer() - playerAnswer);
	m_PlayerOrder.push_back({ value , responseTime , player });
}

int NumericQuestionManager::getNumberOfEntries() const
{
	return m_PlayerOrder.size();
}

std::vector<Color::ColorEnum> NumericQuestionManager::getPlayersOrder()
{
	std::vector<Color::ColorEnum> order;
	std::sort(m_PlayerOrder.begin(), m_PlayerOrder.end(), [this](std::tuple<int, int, Color::ColorEnum> p1, std::tuple<int, int, Color::ColorEnum> p2)
		{
			const auto& [DistFromCorrectAnswer, ResponseTime, Player] = p1;
	const auto& [DistFromCorrectAnswer2, ResponseTime2, Player2] = p2;
	if (DistFromCorrectAnswer < DistFromCorrectAnswer2)
		return true;
	if (DistFromCorrectAnswer == DistFromCorrectAnswer2 && ResponseTime < ResponseTime2)
		return true;
	return false;
		});
	for (auto& player : m_PlayerOrder)
	{
		auto& [DistFromCorrectAnswer, ResponseTime, Player] = player;
		order.push_back(Player);
	}
	return order;
}

QTypeNumerical NumericQuestionManager::getQuestion()
{
	if (m_PlayerOrder.size() == m_playerNr)
	{
		m_PlayerOrder.clear();
	}
	return	m_question;
}