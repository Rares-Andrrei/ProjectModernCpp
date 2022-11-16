#pragma once
#include "Zone.h"
#include <optional>
#include <vector>
//TD :
class Board
{
	uint8_t m_NumberOfPlayers : 2; // Numarul maxim de jucatori este 4
	uint8_t m_BoardWidth : 3;
	uint8_t m_BoardHeight : 3;
	std::vector<std::optional<Zone>> m_board;

public:
	Board(const uint8_t NumberOfPlayers = 2);


private:
	void ChangeBoardDimensions();

};

