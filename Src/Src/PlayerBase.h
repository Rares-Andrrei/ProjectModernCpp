#pragma once
#include "Zone.h"

class PlayerBase: public Zone
{
	int m_lives = 3;
public:
	PlayerBase();
	PlayerBase operator--();
	PlayerBase operator--(int);
	~PlayerBase()= default;
};

