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
	std::string m_username;
	std::string m_nickname;
	Color::ColorEnum m_color : 3;
public:
	Player();
	Player(const std::string& username, const std::string& nickname);
	Player(const std::string& username, const std::string& nickname, const Color::ColorEnum& color);

	Player(const Player& other);
	Player(Player&& other);

	Player& operator=(const Player& other);
	Player& operator=(Player&& other);

	std::string getUsername()const;
	void setUsername(const std::string& first_name);

	void setColor(Color::ColorEnum color);
	Color::ColorEnum getColor()const;
	std::string getColorToString()const;

	void setNickname(const std::string& last_name);
	std::string getNickname()const;
};


