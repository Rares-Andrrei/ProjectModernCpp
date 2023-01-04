#pragma once
#include<string>
#include<iostream>
#pragma once
#include<string>
#include<iostream>


class Player
{
public:
	enum class Color : uint8_t
	{
		None,
		Red,
		Blue,
		Green,
		Yellow
	};
private:
	std::string m_name;
	int m_score;
	Color m_color : 3;

public:
	Player();
	Player(const std::string& name);
	Player(const std::string& name, const Color& color);
	Player::Color getColor()const;
	static std::string ColorToString(Player::Color color);
	static Player::Color stringToColor(const std::string& color);
	void setScore(int score);
	int getScore();
	void setName(const std::string& name);
	void setColor(Color color);
	std::string getName()const;
	friend std::istream& operator>>(std::istream& in, Player& player);
	friend std::ostream& operator<<(std::ostream& out, const Player& player);


};

