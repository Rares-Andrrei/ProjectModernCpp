#pragma once
#include<string>
#include<iostream>
<<<<<<< Updated upstream
#include "ColorEnum.h"
=======
#include  "../Color/Color/Color.h"
>>>>>>> Stashed changes

class PlayerInstance
{
public:

private:
	std::string m_firstName;
	std::string m_lastName;
	Color::ColorEnum m_color : 3;

public:
	PlayerInstance();
	PlayerInstance(const std::string& firstName, const std::string& lastName);
	PlayerInstance(const std::string& firstName, const std::string& lastName, const Color::ColorEnum& color);

	std::string getFirstName()const;
	void setColor(Color::ColorEnum color);
	Color::ColorEnum getColor()const;
	void setFirstName(std::string& first_name);
	void setLastName(std::string& last_name);
	std::string getLastName()const;
};

