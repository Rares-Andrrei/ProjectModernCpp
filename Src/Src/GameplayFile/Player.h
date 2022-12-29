#pragma once
#include<string>
#include<iostream>
#include "../../Color/Color/Color.h"

class Player
{
private:
	std::string m_username;
	std::string m_nickName;
	Color::ColorEnum m_color : 3;

public:
	Player();
	Player(const std::string& username, const std::string& nickName);
	Player(const std::string& username, const std::string& nickName, const Color::ColorEnum& color);
	
	std::string getFirstName()const;
	Color::ColorEnum getColor()const;
	static std::string ColorToString(const Color::ColorEnum& color);
	void setFirstName(const std::string& username);
	void setLastName(const std::string& nickName);
	void setColor(const Color::ColorEnum& color);
	std::string getLastName()const;
};

