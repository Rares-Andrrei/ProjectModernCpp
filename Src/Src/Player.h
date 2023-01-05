#pragma once
#include<iostream>
#include"../../Color/Color/Color.h"
#include<string>


class  Player
{
public:

private:
	std::string m_name;
	int m_score;
	Color::ColorEnum m_color;
public:
	Player();
	Player(const std::string& name);
	Player(const std::string& name, const Color::ColorEnum& color);

	Player(const Player& other);
	Player(Player&& other);

	Player& operator=(const Player& other);
	Player& operator=(Player&& other);

	Player& operator+=(int score);
	Player& operator-=(int score);

	
	std::string getName()const;
	void setName(const std::string& name);

	void setColor(const Color::ColorEnum& color);
	Color::ColorEnum getColor()const;
	std::string getColorToString()const;

	void setScore(int score);
	int getScore()const;
};


