#include "Player.h"

Player::Player()
{
}

std::string Player::Get_First_Name()
{
    return m_first_name;
}

void Player::set_First_Name(std::string& first_name)
{
    this->m_first_name = first_name;
}

void Player::set_Last_Name(std::string& last_name)
{
    this->m_last_name = last_name;
}

std::string Player::Get_Last_Name()
{
    return m_last_name;
}
