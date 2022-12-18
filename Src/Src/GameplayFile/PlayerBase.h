#pragma once
#include "Zone.h"

class PlayerBase: virtual public Zone
{
	int m_lives = 3;
public:
	PlayerBase(Player::Color color);
	
	void DecrementLives();

	PlayerBase operator +(const uint16_t& value);
	friend PlayerBase operator+(const uint16_t& value, PlayerBase& zone);

	friend std::ostream& operator<<(std::ostream& out, const PlayerBase& zona);

	~PlayerBase()= default;
};

