#include "Duel.h"

Duel::Duel(const Color::ColorEnum& player, std::shared_ptr<Zone> zone)
	:m_duelingPlayers{ player, zone->getColor() }, m_zone{ zone }, m_draw{ false }
{
}


void Duel::generateQuestion(QuestionManager& questions)
{
	m_qTypeVariants = questions.randQTypeVariants();
	m_qTypeNumerical = questions.randQTypeNumerical();
}

void Duel::startDuel()
{
	std::string attackerResponse;
	std::string defenderResonse;
	std::cout << m_qTypeVariants.value();
	std::string aux;
	std::getline(std::cin,  aux);
	std::cout << Color::ColorToString(m_duelingPlayers.first) << " player answer:";
	std::getline(std::cin, attackerResponse);
	std::cout << Color::ColorToString(m_duelingPlayers.second) << " player answer:";
	std::getline(std::cin, defenderResonse);

	this->giveAnswers(attackerResponse, defenderResonse);

	if (m_winner == Color::ColorEnum::None && m_draw)
	{
		std::cout << m_qTypeNumerical.value();
		int attackerNumericalResponse, defenderNumericalResponse;
		std::cin >> attackerNumericalResponse >> defenderNumericalResponse;

		this->giveNumericalAnswers({ attackerNumericalResponse,0,m_duelingPlayers.first }, { defenderNumericalResponse,0,m_duelingPlayers.second });
	}
	std::cout << "The Winner is PlayerID:  " << int(m_winner) << " or Color: " << Color::ColorToString(m_winner) << std::endl;
	rewardWinner();
	std::cout << std::endl;
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
}

void Duel::giveNumericalAnswers(std::tuple<int, int, Color::ColorEnum> attacker, std::tuple<int, int, Color::ColorEnum> defender)
{
	m_draw = false;
	auto& [attackerAnswer, attackerResponseTime, attackerPlayer] = attacker;
	auto& [defenderAnswer, defenderResponseTime, defenderPlayer] = defender;
	int corectAnswer = m_qTypeNumerical.value().getAnswer();

	int attackerAnswerError = abs(attackerAnswer - corectAnswer);
	int defenderAnswerError = abs(defenderAnswer - corectAnswer);

	if (attackerAnswerError == defenderAnswerError)
	{
		if (attackerResponseTime == defenderResponseTime)
		{
			m_draw = true;
			return;
		}
		else if (attackerResponseTime < defenderResponseTime)
		{
			m_winner = attackerPlayer;
		}
	}
	else if (attackerAnswerError < defenderAnswerError)
	{
		m_winner = attackerPlayer;
	}
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
		auto isBase = std::dynamic_pointer_cast<PlayerBase>(m_zone);
		if (std::dynamic_pointer_cast<PlayerBase>(m_zone) != nullptr)
		{
			isBase->DecrementLives();
		}
		else if (m_zone->getScore() == 100)
		{
			m_zone->changeOwner(attacker);
		}
		else
		{
			m_zone->DecrementScore();
		}
	}

}

