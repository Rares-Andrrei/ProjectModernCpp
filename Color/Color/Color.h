#pragma once
#ifdef COLOR_EXPORTS
#define COLOR_API __declspec(dllexport)
#else
#define COLOR_API __declspec(dllimport)
#endif

#include <string>
class COLOR_API Color
{
public:
	enum class ColorEnum
	{
		None,
		Red,
		Green,
		Blue,
		Yellow
	};

public:
	static std::string ColorToString(const ColorEnum& color);
	static ColorEnum getColor(int index);
	static ColorEnum getDefaultColor();
	static ColorEnum StringToColor(const std::string& color);
	static int ColorToInt(const ColorEnum& color);
};