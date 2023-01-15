#pragma once
#include "Zone.h"

class PlayerBase: virtual public Zone
{
	int m_lives = 3;
public:
	PlayerBase(const Color::ColorEnum& color);
	uint16_t getNumberOfLifesLeft() const ;
	
	void DecrementLives();
	PlayerBase operator +(const uint16_t& value);
	friend PlayerBase operator+(const uint16_t& value, PlayerBase& zone);
	~PlayerBase()= default;
};

