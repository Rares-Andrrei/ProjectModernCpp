#include "PlayerBase.h"

PlayerBase::PlayerBase(Player::Color color)
	:Zone(color )
{
	this->SetScore(300);
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

std::ostream& operator<<(std::ostream& out, const PlayerBase& zona)
{
	out <<"B:" << Player::ColorToString(zona.m_color) << ' ';
	//out << "\nB:" << (const Zone&)zona;
	

	//out <<"B:"<< static_cast<const Zone&>(zona);
	return out;
}
