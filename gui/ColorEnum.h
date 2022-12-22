#pragma once
#include <cstdlib>
#include <string>
enum class Color :int
{
	None,
	Red,
	Blue,
	Green,
	Yellow
};

std::string ColorToString(Color color);
