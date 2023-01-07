#pragma once
#include "ChooseRegion.h"

class ChooseBase :public ChooseRegion
{
public:
	ChooseBase(QuestionManager& questions);

	void setBaseZone(Board& board);
};

