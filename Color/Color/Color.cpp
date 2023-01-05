#include "Color.h"

std::string Color::ColorToString(const Color::ColorEnum& color)
{
	switch (color)
	{
	case Color::ColorEnum::Red:
		return "red";
	case Color::ColorEnum::Green:
		return "green";
	case Color::ColorEnum::Blue:
		return "blue";
	case Color::ColorEnum::Yellow:
		return "yellow";
	default:
		return "black";
	}
}

Color::ColorEnum Color::getColor(const int& index)
{
	switch (index)
	{
	case 1:
		return Color::ColorEnum::Red;
		break;
	case 2:
		return Color::ColorEnum::Green;
		break;
	case 3:
		return Color::ColorEnum::Blue;
		break;
	case 4:
		return Color::ColorEnum::Yellow;
		break;
	default:
		return Color::ColorEnum::None;
	}
}

Color::ColorEnum Color::getDefaultColor()
{
	return Color::ColorEnum::None;
}

Color::ColorEnum Color::StringToColor(const std::string& color)
{
	if (color == "red")
	{
		return Color::ColorEnum::Red;
	}
	else if (color == "green")
	{
		return Color::ColorEnum::Green;
	}
	else if (color == "blue")
	{
		return Color::ColorEnum::Blue;
	}
	else if (color == "yellow")
	{
		return Color::ColorEnum::Yellow;
	}
	else
	{
		return Color::ColorEnum::None;
	}
}
