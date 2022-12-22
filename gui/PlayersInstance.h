#pragma once
#include<string>
#include<iostream>
#include "ColorEnum.h"

class PlayerInstance
{
public:

private:
	std::string m_firstName;
	std::string m_lastName;
	Color m_color : 3;

public:
	PlayerInstance(const std::string& firstName, const std::string& lastName);
	PlayerInstance(const std::string& firstName, const std::string& lastName, const Color& color);

	std::string getFirstName()const;
	void setColor(Color color);
	Color getColor()const;
	void setFirstName(std::string& first_name);
	void setLastName(std::string& last_name);
	std::string getLastName()const;
};

