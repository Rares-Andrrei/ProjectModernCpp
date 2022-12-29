#include "Player.h"
#include<iostream>
#include<string>


Player::Player()
	:m_color{ Color::getDefaultColor() }, m_username{ "" }, m_nickName{ "" }
{
}

Player::Player(const std::string& username, const std::string& nickname)
	:m_color{ Color::getDefaultColor() }, m_username{ username }, m_nickName{ nickname }
{
}

Player::Player(const std::string& username, const std::string& nickname, const Color::ColorEnum& color)
	:m_color{ color }, m_username{ username }, m_nickName{ nickname }
{
}
std::string Player::getFirstName() const
{
	return m_username;
}

void Player::setFirstName(const std::string& username)
{
	this->m_username = username;
}

void Player::setLastName(const std::string& nickname)
{
	this->m_nickName = nickname;
}

void Player::setColor(const Color::ColorEnum& color)
{
	this->m_color = color;
}
Color::ColorEnum Player::getColor() const
{
	return m_color;
}

std::string Player::ColorToString(const Color::ColorEnum& color)
{
	return Color::ColorToString(color);
}

std::string Player::getLastName() const
{
	return m_nickName;
}