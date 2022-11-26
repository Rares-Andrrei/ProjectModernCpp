#pragma once
#include "Zone.h"

class PlayerBase: public Zone
{
	int m_lives = 3;
public:
	PlayerBase(Player::Color color);
	PlayerBase operator--();
	PlayerBase operator--(int);
	~PlayerBase()= default;
};

