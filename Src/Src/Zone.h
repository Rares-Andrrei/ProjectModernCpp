#pragma once
#include <cstdint>
#include "Player.h"

class Zone
{
protected:
	uint16_t m_score;
	bool m_captured;
	Player m_player;
public:
	Zone() = default;
	void SetScore(const uint16_t& score = 100);
	void SetPlayer(Player player);
	Zone operator +(const uint16_t& value);
	friend Zone operator+(const uint16_t& value, Zone& zone);
	void DecrementScore(); // folosit pentru clasa  AVANTAJE
	friend std::ostream& operator<<(std::ostream& out, const Zone& zona);
	uint16_t getScore();
	~Zone() = default;
};