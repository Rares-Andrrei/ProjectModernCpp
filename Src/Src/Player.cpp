#include "Player.h"



Player::Player()
	:m_color{ Color::getDefaultColor() }, m_name{ }, m_score{ 300 }
{
}

Player::Player(const std::string& name)
	:m_name{ name }, m_color{ Color::getDefaultColor() }, m_score{ 300 }
{
}

Player::Player(const std::string& name, const Color::ColorEnum& color)
	:m_name{ name }, m_color{ color }, m_score{ 300 }
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
	this->m_score = other.m_score;
	this->m_name = other.m_name;

	return *this;
}

Player& Player::operator=(Player&& other)
{
	this->m_color = other.m_color;
	this->m_score = other.m_score;
	this->m_name = other.m_name;

	new(&other) Player;

	return *this;
}

Player& Player::operator+=(int score)
{
	m_score += score;
	return *this;
}

Player& Player::operator-=(int score)
{
	m_score -= score;
	return *this;
}

std::string Player::getName() const
{
	return m_name;
}

void Player::setColor(const Color::ColorEnum& color)
{
	m_color = color;
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

void Player::setName(const std::string& name)
{
	this->m_name = name;
}

