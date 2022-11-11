#include "Player.h"
#include<iostream>
#include<string>
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

std::istream& operator>>(std::istream& in,  Player & player)
{ 
    in >> player.m_first_name >> player.m_last_name;
    return in;
}

std::ostream& operator<<(std::ostream& out, Player& player)
{
    out <<"Numele dumneavoastra este: "<< player.m_first_name << "\n"<<"Prenumele dumneavoastra este: " << player.m_last_name;
    return out;// TODO: insert return statement here
}
