#include "PlayersInstance.h"
#include<iostream>
#include<string>


PlayerInstance::PlayerInstance(const std::string& firstName, const std::string& lastName)
{
    this->m_firstName = firstName;
    this->m_lastName = lastName;
    this->m_color = Color::None;
}

PlayerInstance::PlayerInstance(const std::string& firstName, const std::string& lastName, const Color& color)
{
    this->m_firstName = firstName;
    this->m_lastName = lastName;
    this->m_color = color;
}
std::string PlayerInstance::getFirstName() const
{
    return m_firstName;
}

void PlayerInstance::setFirstName(std::string& const first_name)
{
    this->m_firstName = first_name;
}

void PlayerInstance::setLastName(std::string& const last_name)
{
    this->m_lastName = last_name;
}

void PlayerInstance::setColor(Color const color)
{
    this->m_color = color;
}
Color PlayerInstance::getColor() const
{
    return m_color;
}

std::string PlayerInstance::getLastName() const
{
    return m_lastName;
}