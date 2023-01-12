#include "BoardInterpretation.h"

BoardInterpretation::BoardInterpretation(int NumberOfPlayers)
{
	generateBoard(NumberOfPlayers);
	generateNeighbours();
}

void BoardInterpretation::generateBoard(int NumberOfPlayers)
{
	if (NumberOfPlayers == 2)
	{
		k_boardHeight = 3;
		k_boardWidth = 3;
		return;
	}
	else if (NumberOfPlayers == 3)
	{
		k_boardWidth = 3; // latime
		k_boardHeight = 5; // lungime 
		return;
	}
	else {
		k_boardHeight = 6;
		k_boardWidth = 4;
	}
	m_board.resize(k_boardHeight * k_boardWidth + 1);
	m_board[k_boardHeight * k_boardWidth] = Color::getDefaultColor();
}

void BoardInterpretation::generateNeighbours()
{
	for (int i = 0; i < k_boardHeight * k_boardWidth; i++)
	{
		if (i - k_boardWidth >= 0) // verificare prima linie
			m_zonesNeighbours[i].push_back({ i - k_boardWidth,m_board[i - k_boardWidth] });
		if (i % k_boardWidth == 1)// verificare stanga
			m_zonesNeighbours[i].push_back({ i - 1,m_board[i - 1] });
		if (i % k_boardWidth == k_boardWidth - 1) // verificare dreapta
			m_zonesNeighbours[i].push_back({i+1,m_board[i+1]});
		//verificare ultima linie
	}
}
