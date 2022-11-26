#pragma once
#include "Zone.h"
#include <optional>
#include <vector>

class Board
{
	uint8_t m_NumberOfPlayers; // Numarul maxim de jucatori este 4
	uint8_t m_BoardWidth;
	uint8_t m_BoardHeight;
	std::vector<std::optional<Zone>> m_board;
	int m_totalScore;

public:
	Board(const uint8_t NumberOfPlayers = 2);
	using Position = std::pair<int, int>;
	friend std::ostream& operator <<(std::ostream& out, Board board);
	const std::optional<Zone>& operator[](const Position& indices) const;
	std::optional<Zone>& operator[](const Position& indices);
	void ObtainTotalScore();
	int getTotalScore();

private:
	void ChangeBoardDimensions();
};