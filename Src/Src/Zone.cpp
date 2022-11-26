#include "Zone.h"

void Zone::SetScore(const uint16_t& score)
{
	this->m_score = score;
}

void Zone::SetPlayer(Player player)
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

uint16_t Zone::getScore()
{
	return this->m_score;
}

Zone operator+(const uint16_t& value, Zone& zone)
{
	return  zone + value;
}

std::ostream& operator<<(std::ostream& out, const Zone& zona)
{
	//out << zona.Color<<' '; 
	// aceasta operatie necesita un nou tip de date : Color, in clasa jucator.

	out << zona.m_player << ' ';


	return out;
}