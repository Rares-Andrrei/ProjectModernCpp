#include "Zone.h"

Zone::Zone(const Color::ColorEnum& color)
	:m_color{ color }, m_score{ 100 }
{
}

Zone::Zone()
	:m_color{ Color::getDefaultColor() }, m_score{ 100 }
{
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

void Zone::changeOwner(Color::ColorEnum newOwnerColor)
{
	m_color = newOwnerColor;
}

uint16_t Zone::getScore()
{
	return this->m_score;
}

Color::ColorEnum Zone::getColor()
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
	out << Color::ColorToString(zona.m_color) << ' ';

	return out;
}