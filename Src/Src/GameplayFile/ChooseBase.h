#pragma once
#include <cstdlib>
#include "Player.h"
#include "PlayerBase.h"
#include "QuestionManager.h"
#include "Board.h"
#include <array>
#include <queue>
#include "ChooseRegion.h"
#include <memory>

class ChooseBase :public ChooseRegion
{
public:
	ChooseBase(QuestionManager& questions);

	void setBaseZone(Board& board);
};

