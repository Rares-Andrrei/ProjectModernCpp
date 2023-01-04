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
	const char* m_username;
	int m_score;
	Color::ColorEnum m_color : 3;
public:
	Player();
	Player(const const char*& username);
	Player(const const char*& username, const Color::ColorEnum& color);

	Player(const Player& other);
	Player(Player&& other);

	Player& operator=(const Player& other);
	Player& operator=(Player&& other);

	const char* getUsername()const;
	void setUsername(const const char*& first_name);

	void setColor(const Color::ColorEnum& color);
	Color::ColorEnum getColor()const;
	std::string getColorToString()const;

	void setScore(int score);
	int getScore()const;
};


