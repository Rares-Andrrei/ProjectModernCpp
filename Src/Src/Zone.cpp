#include "Zone.h"

void Zone::SetScore(const uint16_t& score)
{
	this->m_score = score;
}

void Zone::SetPlayer(Player* player)
{
	this->m_player = player;
	if (m_captured == true)// daca zona a capturata de la alt jucator , incrementam valoarea acestia cu 100;
	{
		this->m_score += 100;
	}
}

Zone Zone::operator+(const uint16_t& value)
{
	this->m_score += value;
	return *this;
}
