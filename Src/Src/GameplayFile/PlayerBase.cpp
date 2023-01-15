#include "PlayerBase.h"

PlayerBase::PlayerBase(const Color::ColorEnum& color)
	:Zone(color)
{
	this->SetScore(300);
}

uint16_t PlayerBase::getNumberOfLifesLeft() const
{
	return m_lives;
}

void PlayerBase::DecrementLives()
{
	m_lives--;
}

PlayerBase PlayerBase::operator+(const uint16_t& value)
{
	this->m_score += value;
	return *this;
}

PlayerBase operator+(const uint16_t& value, PlayerBase& zone)
{
	return  zone + value;
}