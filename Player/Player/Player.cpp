#include "Player.h"



Player::Player()
	:m_color{ Color::getDefaultColor() }, m_username{ "" }, m_nickname{ "" }
{
}

Player::Player(const const char*& username, const const char*& nickname)
	:m_username{ username }, m_nickname{ nickname }, m_color{ Color::getDefaultColor() }
{
}

Player::Player(const const char*& username, const const char*& nickname, const Color::ColorEnum& color)
	:m_username{ username }, m_nickname{ nickname }, m_color{ color }
{
}

Player::Player(const Player& other)
{
	*this = other;
}

Player::Player(Player&& other)
{
	*this = std::move(other);
}

Player& Player::operator=(const Player& other)
{
	this->m_color = other.m_color;
	this->m_username = other.m_username;
	this->m_nickname = other.m_nickname;

	return *this;
}

Player& Player::operator=(Player&& other)
{
	this->m_color = other.m_color;
	this->m_username = other.m_username;
	this->m_nickname = other.m_nickname;

	new(&other) Player;

	return *this;
}

const char* Player::getUsername() const
{
	return m_username;
}

void Player::setColor(Color::ColorEnum color)
{
	this->m_color = color;
}

Color::ColorEnum Player::getColor() const
{
	return m_color;
}

const char* Player::getColorToString() const
{
	return Color::ColorToString(m_color);
}

void Player::setUsername(const const char*& first_name)
{
	this->m_username = first_name;
}

void Player::setNickname(const const char*& last_name)
{
	this->m_nickname = last_name;
}

const char* Player::getNickname() const
{
	return m_nickname;
}
