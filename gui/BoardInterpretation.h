#pragma once
#include <optional>
#include <memory>
#include <vector>
#include "../Color/Color/Color.h"
#include <unordered_map>

class BoardInterpretation
{
	std::unordered_map<int, std::unordered_map<int, std::shared_ptr<Color::ColorEnum>>> m_zonesNeighbours;
	std::vector<std::tuple<int,std::shared_ptr<Color::ColorEnum>,bool>> m_board;
	int k_boardHeight;
	int k_boardWidth;

public:
	BoardInterpretation(int NumberOfPlayers = 2);
	~BoardInterpretation() = default;

	bool AddZoneAsBase(int IdZone, const Color::ColorEnum& color);
	bool AddCloseZone(int IdZone, const Color::ColorEnum& color);

	bool checkBoardFull();

private:
	void generateBoard(int NumberOfPlayers);
	void generateNeighbours();
	bool checkIfPlayerHasValidMoved(const Color::ColorEnum& color);
};

