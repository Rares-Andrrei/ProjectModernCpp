#include "NumericQuestionManager.h"

NumericQuestionManager::NumericQuestionManager(const QTypeNumerical& question)
	: m_question{ question }
{
}

void NumericQuestionManager::setQuestion(const QTypeNumerical& question)
{
	m_question = question;
}

void NumericQuestionManager::addPlayerResponse(const int& responseTime, const int& playerAnswer, const Color::ColorEnum& player)
{
	m_PlayerOrder.push({ playerAnswer , responseTime , player });
	std::vector<int> v;
}

int NumericQuestionManager::getNumberOfEntries() const
{
	return m_PlayerOrder.size();
}

std::vector<Color::ColorEnum> NumericQuestionManager::getPlayersOrder()
{
	std::vector<Color::ColorEnum> order;
	while (!m_PlayerOrder.empty())
	{
		auto& [PlayerResponse, ResponseTime, PlayerColor] = m_PlayerOrder.top();
		order.push_back(PlayerColor);
		m_PlayerOrder.pop();
	}
	return order;
}

QTypeNumerical NumericQuestionManager::getQuestion()
{
	return	m_question;
}