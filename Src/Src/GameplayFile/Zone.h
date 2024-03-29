#pragma once
#include <cstdint>
#include <iostream>
#include "../../Color/Color/Color.h"

class Zone
{
protected:
	uint16_t m_score;
	Color::ColorEnum m_color;
public:
	Zone();
	Zone(const Color::ColorEnum& color);
	void SetScore(const uint16_t& score = 100);

	//Operator for score
	Zone operator +(const uint16_t& value);
	friend Zone operator+(const uint16_t& value, Zone& zone);

	//Operator for score
	Zone operator -(const uint16_t& value);
	friend Zone operator-(const uint16_t& value, Zone& zone);

	void DecrementScore(); // folosit pentru clasa  AVANTAJE si duel
	void changeOwner(Color::ColorEnum newOwnerColor);

	friend std::ostream& operator<<(std::ostream& out, const Zone& zona);

	uint16_t getScore();
	Color::ColorEnum getColor();
	virtual ~Zone() = default;
};