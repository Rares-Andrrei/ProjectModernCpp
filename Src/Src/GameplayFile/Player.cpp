#include "Player.h"
#include<iostream>
#include<string>


Player::Player()
    :  m_name{ "" }, m_color{Player::Color::None}, m_score{ 0 }
{
}

Player::Player(const std::string& name) : m_name{name}, m_color{Player::Color::None}, m_score { 0 }
{
}

Player::Player(const std::string& name, const Color& color) : m_name{ name }, m_color{color}, m_score{ 0 }
{
}


void Player::setColor(Color const color) 
{
    this->m_color = color;
}
std::string Player::getName() const
{
    return m_name;
}
Player::Color Player::getColor() const
{
    return m_color;
}

std::string Player::ColorToString(Player::Color color)
{
    switch (color)
    {
    case Color::None:
        return "None";
    case Color::Red:
        return "Red";
    case Color::Blue:
        return "Blue";
    case Color::Green:
        return "Green";
    case Color::Yellow:
        return "Yellow";
    default: 
        return "";
    }
}

void Player::setScore(int score)
{
    m_score = score;
}

int Player::getScore()
{
    return m_score;
}

void Player::setName(std::string& name)
{
    m_name = name;
}


std::istream& operator>>(std::istream& in,  Player & player)
{ 
    in >> player.m_name;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Player& player)
{
    out << "Numele dumneavoastra este: " << player.m_name<<"\n";
    out << "Culoarea dumneavoastra este: ";
    out << Player::ColorToString(player.m_color);

    return out;
   
}
