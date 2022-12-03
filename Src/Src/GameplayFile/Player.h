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
	std::string m_firstName;
	std::string m_lastName;
	Color m_color:3;

public:
	Player(const std::string& firstName,const std::string& lastName);
	Player(const std::string& firstName, const std::string& lastName, const Color& color);
	std::string getFirstName()const;
	Player::Color getColor()const;
	static std::string ColorToString(Player::Color color);
	void setFirstName(std::string& first_name);
	void setLastName(std::string& last_name);
	void setColor(Color color) ;
	std::string getLastName()const;
	friend std::istream& operator>>(std::istream& in,  Player & player);
	friend std::ostream& operator<<(std::ostream& out,const Player& player);
	

};

