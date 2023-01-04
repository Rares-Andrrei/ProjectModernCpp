#pragma once
#include <qstring.h>
#include "../Color/Color/Color.h"

class  PlayerQString
{
private:
	QString m_name;
	int m_score;
	Color::ColorEnum m_color : 3;

public:

	PlayerQString();
	PlayerQString(const QString& name);
	PlayerQString(const QString& name, const Color::ColorEnum& color);

	PlayerQString(const PlayerQString& other);
	PlayerQString(PlayerQString&& other);

	PlayerQString& operator=(const PlayerQString& other);
	PlayerQString& operator=(PlayerQString&& other);

	PlayerQString& operator+=(int score);
	PlayerQString& operator-=(int score);

	QString getName()const;
	void setName(const QString& name);

	void setColor(const Color::ColorEnum& color);
	Color::ColorEnum getColor()const;
	std::string getColorToString()const;

	void setScore(int score);
	int getScore()const;
};



