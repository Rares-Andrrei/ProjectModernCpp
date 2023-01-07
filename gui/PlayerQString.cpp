#include "PlayerQString.h"



PlayerQString::PlayerQString()
	:m_color{ Color::getDefaultColor() }, m_name{ }, m_score{ 300 }
{
}

PlayerQString::PlayerQString(const QString& name)
	:m_name{ name }, m_color{ Color::getDefaultColor() }, m_score{ 300 }
{
}

PlayerQString::PlayerQString(const QString& name, const Color::ColorEnum& color)
	:m_name{ name }, m_color{ color }, m_score{ 300 }
{
}

PlayerQString::PlayerQString(const PlayerQString& other)
{
	*this = other;
}

PlayerQString::PlayerQString(PlayerQString&& other)
{
	*this = std::move(other);
}

PlayerQString& PlayerQString::operator=(const PlayerQString& other)
{
	this->m_color = other.m_color;
	this->m_name = other.m_name;
	this->m_score = other.m_score;

	return *this;
}

PlayerQString& PlayerQString::operator=(PlayerQString&& other)
{
	this->m_color = other.m_color;
	this->m_name = other.m_name;
	this->m_score = other.m_score;

	new(&other) PlayerQString;

	return *this;
}

PlayerQString& PlayerQString::operator+=(int score)
{
	m_score += score;
	return *this;
}

PlayerQString& PlayerQString::operator-=(int score)
{
	m_score -= score;
	return *this;
}

QString PlayerQString::getName() const
{
	return m_name;
}

void PlayerQString::setColor(const Color::ColorEnum& color)
{
	this->m_color = color;
}

Color::ColorEnum PlayerQString::getColor() const
{
	return m_color;
}

std::string PlayerQString::getColorToString() const
{
	return Color::ColorToString(m_color);
}

void PlayerQString::setScore(int score)
{
	m_score = score;
}

int PlayerQString::getScore() const
{
	return m_score;
}

void PlayerQString::setName(const QString& name)
{
	this->m_name = name;
}

