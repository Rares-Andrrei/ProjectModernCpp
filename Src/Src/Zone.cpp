#include "Zone.h"

void Zone::SetScore(const uint16_t& score)
{
	this->m_score = score;
}

void Zone::SetPlayer(Player* player)
{
	this->m_player = player;
	this->m_score += 100;
}

Zone Zone::operator+(const uint16_t& value)
{
	this->m_score += value;
	return *this;
}

void Zone::DecrementScore()// scade scorul cu 100 , atunci cand alegem un avantaj 
{
	if (this->m_score >= 200)
	{
		this->m_score -= 100;
	}
}

Zone operator+(const uint16_t& value, Zone& zone)
{
	return  zone + value;
}
