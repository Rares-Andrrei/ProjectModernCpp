#pragma once
#include <optional>
#include <vector>
#include "../Color/Color/Color.h"
#include <unordered_map>

class BoardInterpretation
{
	std::unordered_map<int, std::vector<std::pair<int, std::optional<Color::ColorEnum>>>> m_zonesNeighbours;
	std::vector<std::optional<Color::ColorEnum>> m_board;
	int k_boardHeight;
	int k_boardWidth;


public:
	BoardInterpretation(int NumberOfPlayers);
	~BoardInterpretation();


private:
	void generateBoard(int NumberOfPlayers);
	void generateNeighbours();
};

