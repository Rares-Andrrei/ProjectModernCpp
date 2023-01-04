#include "Player.h"



Player::Player()
	:m_color{ Color::getDefaultColor() }, m_username{ }
{
}

Player::Player(const const char*& username)
	:m_username{ username }, m_color{ Color::getDefaultColor() }
{
}

Player::Player(const const char*& username, const Color::ColorEnum& color)
	:m_username{ username }, m_color{ color }
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

	return *this;
}

Player& Player::operator=(Player&& other)
{
	this->m_color = other.m_color;
	this->m_username = other.m_username;

	new(&other) Player;

	return *this;
}

const char* Player::getUsername() const
{
	return m_username;
}

void Player::setColor(const Color::ColorEnum& color)
{
	this->m_color = color;
}

Color::ColorEnum Player::getColor() const
{
	return m_color;
}

std::string Player::getColorToString() const
{
	return Color::ColorToString(m_color);
}

void Player::setScore(int score)
{
	m_score = score;
}

int Player::getScore() const
{
	return m_score;
}

void Player::setUsername(const const char*& first_name)
{
	this->m_username = first_name;
}

