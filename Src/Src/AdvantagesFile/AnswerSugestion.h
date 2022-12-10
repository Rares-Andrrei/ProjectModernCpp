#pragma once
#include<iostream>
class AnswerSugestion
{
	bool m_used;
public:
	AnswerSugestion();
	int useAdvantage(int answer);
	bool isUsed();
};