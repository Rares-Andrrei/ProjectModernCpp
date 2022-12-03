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

Zone Zone::operator-(const uint16_t& value)
{
	this->m_score += value;
	return *this;
}

void Zone::DecrementScore()// scade scorul cu 100 , atunci cand alegem un avantaj sau in cadrul duelului
{
	if (this->m_score >= 200)
	{
		this->m_score -= 100;
	}
}


void Zone::changeOwner(Player::Color newOwnerColor)
{
	m_color = newOwnerColor;
}

uint16_t Zone::getScore()
{
	return this->m_score;
}

Player::Color Zone::getColor()
{
	return m_color;
}
Zone operator+(const uint16_t& value, Zone& zone)
{
	return  zone + value;
}

Zone operator-(const uint16_t& value, Zone& zone)
{
	return  zone - value;
}

std::ostream& operator<<(std::ostream& out, const Zone& zona)
{
	//out << zona.Color<<' '; 
	// aceasta operatie necesita un nou tip de date : Color, in clasa jucator.
	out << Player::ColorToString(zona.m_color) << ' ';


	return out;
}