#pragma once
#include <cstdint>
#include "Player.h"

class Zone
{
protected:
	uint16_t m_score;
	bool m_captured;
	Player::Color m_color;
public:
	Zone(Player::Color color) ;
	void SetScore(const uint16_t& score = 100);

	//Operator for score
	Zone operator +(const uint16_t& value);
	friend Zone operator+(const uint16_t& value, Zone& zone);

	//Operator for score
	Zone operator -(const uint16_t& value);
	friend Zone operator-(const uint16_t& value, Zone& zone);

	void DecrementScore(); // folosit pentru clasa  AVANTAJE si duel
	void changeOwner(Player::Color newOwnerColor);
	friend std::ostream& operator<<(std::ostream& out, const Zone& zona);
	uint16_t getScore();
	Player::Color getColor();
	~Zone() = default;
};