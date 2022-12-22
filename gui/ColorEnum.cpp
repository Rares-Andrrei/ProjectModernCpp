#include "ColorEnum.h"

std::string ColorToString(Color color)
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
