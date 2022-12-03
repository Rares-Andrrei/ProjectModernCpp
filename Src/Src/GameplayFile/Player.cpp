#include "Player.h"
#include<iostream>
#include<string>


Player::Player(const std::string& firstName, const std::string& lastName)
{
    this->m_firstName = firstName;
    this->m_lastName = lastName;
    this->m_color = Color::None;
}

Player::Player(const std::string& firstName, const std::string& lastName, const Color& color)
{
    this->m_firstName = firstName;
    this->m_lastName = lastName;
    this->m_color = color;
}
std::string Player::getFirstName() const
{
    return m_firstName;
}

void Player::setFirstName(std::string& const first_name)
{
    this->m_firstName = first_name;
}

void Player::setLastName(std::string& const last_name) 
{
    this->m_lastName = last_name;
}

void Player::setColor(Color const color) 
{
    this->m_color = color;
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

std::string Player::getLastName() const
{
    return m_lastName;
}

std::istream& operator>>(std::istream& in,  Player & player)
{ 
    in >> player.m_firstName >> player.m_lastName;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Player& player)
{
    out << "Prenumele dumneavoastra este: " << player.m_firstName << "\n" << "Numele dumneavoastra este: " << player.m_lastName<<"\n";
    out << "Culoarea dumneavoastra este: ";
    out << Player::ColorToString(player.m_color);

    return out;
   
}
