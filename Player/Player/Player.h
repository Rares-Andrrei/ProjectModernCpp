#pragma once
#include<iostream>
#include"../../Color/Color/Color.h"
#include<string>
#ifdef PLAYER_EXPORTS
#define PLAYER_API __declspec(dllexport)
#else
#define PLAYER_API __declspec(dllimport)
#endif


class PLAYER_API Player
{
public:

private:
	 std::string m_firstName;
	 std::string m_lastName;
	Color::ColorEnum m_color : 3;
public:
	Player() = default;
	Player(const std::string& firstName, const std::string& lastName);
	Player(const std::string& firstName, const std::string& lastName, const Color::ColorEnum& color);

	std::string getFirstName()const;
	void setColor(Color::ColorEnum color);
	Color::ColorEnum getColor()const;
	std::string getColorToString()const;
	void setFirstName(std::string& first_name);
	void setLastName(std::string& last_name);
	std::string getLastName()const;
};


