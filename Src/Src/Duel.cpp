#include "Duel.h"

bool Duel::isDraw() const
{
	return m_draw;
}

Duel::Duel(Player::Color player, Zone* zone)
{
	m_duelingPlayers.first = player;
	m_zone = zone;
	m_duelingPlayers.second = m_zone->getColor();
	m_winner = Player::Color::None;
	m_draw = false;
}


void Duel::generateQuestion(QuestionManager& questions)
{
	if (!m_qTypeVariants)
	{
		m_qTypeVariants = questions.randQTypeVariants();
	}
	else
	{
		m_qTypeNumerical = questions.randQTypeNumerical();
	}
}

QTypeVariants Duel::getQTypeVariants()
{
	return m_qTypeVariants.value();
}

QTypeNumerical Duel::getQTypeNumerical()
{
	return m_qTypeNumerical.value();
}

void Duel::giveAnswers(int attackerAnswer, int defenderAnswer)
{
	auto& [attacker, defender] = m_duelingPlayers;
	const int corectAnswer = m_qTypeNumerical.value().getAnswer();
	if (attackerAnswer == defenderAnswer == corectAnswer)
	{
		return;
	}
	else if (attackerAnswer == corectAnswer)
	{
		m_winner = attacker;
	}
	else if (defenderAnswer == corectAnswer)
	{
		m_winner = defender;
	}

}

void Duel::giveAnswers(std::string attackerAnswer, std::string defenderAnswer)
{
	auto& [attacker, defender] = m_duelingPlayers;
	std::string corectAnswer = m_qTypeVariants.value().getAnswer();
	if (attackerAnswer == defenderAnswer)
	{
		if (attackerAnswer == corectAnswer)
		{
			m_draw = true;
			return;
		}
	}
	else if (attackerAnswer == corectAnswer)
	{
		m_winner = attacker;
	}
	else if (defenderAnswer == corectAnswer)
	{
		m_winner = defender;
	}
}

Player::Color Duel::getWinner()
{
	return m_winner;
}

void Duel::rewardWinner()
{
	auto& [attacker, defender] = m_duelingPlayers;
	if (m_winner == defender)
	{
		*m_zone = *m_zone + 100;
	}
	else
	{
		if (m_zone->getScore() == 100)
		{
			m_zone->changeOwner(attacker);
		}
		else
		{
			m_zone->DecrementScore();
		}
	}
}

