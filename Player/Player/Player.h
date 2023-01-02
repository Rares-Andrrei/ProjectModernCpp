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
	const char* m_nickname;
	Color::ColorEnum m_color : 3;
public:
	Player();
	Player( const const char*& username, const const char*& nickname);
	Player(const const char*& username, const const char*& nickname, const Color::ColorEnum& color);

	Player(const Player& other);
	Player(Player&& other);

	Player& operator=(const Player& other);
	Player& operator=(Player&& other);

	const char* getUsername()const;
	void setUsername(const const char*& first_name);

	void setColor(Color::ColorEnum color);
	Color::ColorEnum getColor()const;
	const char* getColorToString()const;

	void setNickname(const const char*& last_name);
	const char* getNickname()const;
};


