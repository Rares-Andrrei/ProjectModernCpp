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
private:

public:
	ChooseBase(QuestionManager& questions, const uint16_t& numberOfPlayers);
	///selectare si afisare intrebare random
	
	void setBaseZone(Board& board);
};

