#include "Zone.h"

Zone::Zone(Player::Color color)
{
	this->m_color = color;
	this->m_score = 100;
}

void Zone::SetScore(const uint16_t& score)
{
	this->m_score = score;
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

	out << Player::ColorToString(zona.m_color) << ' ';


	return out;
}