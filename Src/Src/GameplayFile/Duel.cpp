#include "Duel.h"

Duel::Duel(const Color::ColorEnum& player, std::shared_ptr<Zone> zone, int zoneId, std::shared_ptr<Database> db)
	:m_duelingPlayers{ player, zone->getColor() }, m_zone{ zone }, m_draw{ false }, m_zoneId{ zoneId }, m_db{ db }, m_numerical{NumericQuestionManager(2)}
{
	generateQuestion();
}

void Duel::getDuelInfo(Color::ColorEnum& c1, Color::ColorEnum& c2, int& zoneId)
{
	c1 = m_duelingPlayers.first;
	c2 = m_duelingPlayers.second;
	zoneId = m_zoneId;
}

void Duel::setDuelVaraintsAnswer(Color::ColorEnum color, int variant)
{
	m_responses[color] = variant;
}

void Duel::setNumericalAnswer(int time, int response, const Color::ColorEnum& color)
{
	m_numerical.addPlayerResponse(time, response, color);
}

QTypeVariants Duel::getQTypeVariants()
{
	return m_qTypeVariants.value();
}

QTypeNumerical Duel::getQTypeNumerical()
{
	return m_numerical.getQuestion();
}

bool Duel::isDraw()
{
	return m_draw;
}

Color::ColorEnum Duel::getAttacker()
{
	return m_duelingPlayers.first;
}

void Duel::setWinner(Board& board)
{
	std::vector<Color::ColorEnum> m_winners;
	if (m_draw)
	{
		m_winners.push_back(m_numerical.getPlayersOrder()[0]);
	}
	else
	{
		for (auto resp : m_responses)
		{
			if (resp.second == m_qTypeVariants->getAnswerIndex())
			{
				m_winners.push_back(resp.first);
			}
		}
	}
	if (m_winners.size() == 0)
	{
		m_state = DuelState::Lose;
		return;
	}
	else if (m_winners.size() == 1)
	{
		auto& [attacker, defender] = m_duelingPlayers;
		auto isBase = std::dynamic_pointer_cast<PlayerBase>(m_zone);
		if (m_winners[0] == defender && std::dynamic_pointer_cast<PlayerBase>(m_zone) == nullptr)
		{
			*m_zone = *m_zone + 100;
			m_updatedZones.push_back(m_zone);
			m_state = DuelState::Win;
			return;
		}
		else if (m_winners[0] == defender && std::dynamic_pointer_cast<PlayerBase>(m_zone) != nullptr)
		{
			m_state = DuelState::Lose;
			return;
		}
		else
		{
			if (std::dynamic_pointer_cast<PlayerBase>(m_zone) != nullptr)
			{
				isBase->DecrementLives();
				if (isBase->getNumberOfLifesLeft() == 0)
				{
					Color::ColorEnum conquerdPlayer = isBase->getColor();
					int zoneId = 0;
					while (board[zoneId] != board.end())
					{
						if (board[zoneId] == isBase)
						{
							board[zoneId].reset();
							board[zoneId] = std::make_shared<Zone>(attacker);
							m_updatedZones.push_back(board[zoneId]);
						}
						else if (board[zoneId]->getColor() == attacker)
						{
							board[zoneId]->changeOwner(attacker);
							m_updatedZones.push_back(board[zoneId]);
						}
						zoneId++;
					}
					m_state = DuelState::Win;
					return;
				}
				else
				{
					m_updatedZones.push_back(m_zone);
					m_state = DuelState::lifeTaken;
					return;
				}

			}
			else if (m_zone->getScore() == 100)
			{
				m_zone->changeOwner(attacker);
				m_updatedZones.push_back(m_zone);
				m_state = DuelState::Win;
				return;
			}
			else
			{
				m_zone->DecrementScore();
				m_updatedZones.push_back(m_zone);
				m_state = DuelState::Win;
				return;
			}
		}
	}
	else
	{
		m_draw = true;
		m_state = DuelState::Draw;
		return;
	}

}

Duel::DuelState Duel::getState()
{
	if (m_state.has_value())
	{
		return m_state.value();
	}
	return DuelState::None;
}

int Duel::getZoneId()
{
	return m_zoneId;
}

std::vector<std::shared_ptr<Zone>> Duel::getUpdatedZones()
{
	return m_updatedZones;
}

void Duel::generateQuestion()
{
	m_qTypeVariants = m_db->randQTypeVariants();
	m_numerical.setQuestion(m_db->randQTypeNumerical());
}

