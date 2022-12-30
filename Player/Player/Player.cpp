#include "Player.h"



Player::Player(const std::string& firstName, const std::string& lastName)
{
	this->m_firstName = firstName;
	this->m_lastName = lastName;
	this->m_color = Color::getDefaultColor();
}

Player::Player(const std::string& firstName, const std::string& lastName, const Color::ColorEnum& color)
{
	this->m_firstName = firstName;
	this->m_lastName = lastName;
	this->m_color = color;
}

std::string Player::getFirstName() const
{
	return m_firstName;
}

void Player::setColor(Color::ColorEnum color)
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

void Player::setFirstName(std::string& first_name)
{
	this->m_firstName = first_name;
}

void Player::setLastName(std::string& last_name)
{
	this->m_lastName = last_name;
}

std::string Player::getLastName() const
{
	return m_lastName;
}
