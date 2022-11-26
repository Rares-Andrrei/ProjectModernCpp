#include "Player.h"
#include<iostream>
#include<string>


Player::Player(std::string firstName, std::string lastName)
{
    this->m_firstName = firstName;
    this->m_lastName = lastName;
    this->m_color = Color::None;
}

Player::Player(std::string firstName, std::string lastName, Color color)
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
Color Player::getColor() const
{
    return m_color;
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
    out <<"Numele dumneavoastra este: "<< player.m_first_name << "\n"<<"Prenumele dumneavoastra este: " << player.m_last_name;
    return out;// TODO: insert return statement here
    out << "Prenumele dumneavoastra este: " << player.m_firstName << "\n" << "Numele dumneavoastra este: " << player.m_lastName<<"\n";
    out << "Culoarea dumneavoastra este: ";
    Color color = player.getColor();
    switch (color)
    {
    case Color::None:
        out << "None";
        break;
    case Color::Red:
        out << "Red";
        break;
    case Color::Blue:
        out << "Blue";
        break;
    case Color::Green:
        out << "Green";
        break;
    case Color::Yellow:
        out << "Yellow";
        break;
    }
    return out;
   
}
