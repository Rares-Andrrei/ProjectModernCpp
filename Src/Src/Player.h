#pragma once
#include<string>
#include<iostream>
class Player
{
private:
	std::string m_first_name;
	std::string m_last_name;
public:
	Player();
	std::string Get_First_Name();
	void set_First_Name(std::string& first_name);
	void set_Last_Name(std::string& last_name);
	std::string Get_Last_Name();
	friend std::istream& operator>>(std::istream& in,  Player & player);
	friend std::ostream& operator<<(std::ostream& out, Player& player);
	

};

