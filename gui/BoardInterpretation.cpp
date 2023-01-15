#include "BoardInterpretation.h"

BoardInterpretation::BoardInterpretation(int NumberOfPlayers)
{
	generateBoard(NumberOfPlayers);
	generateNeighbours();
}

bool BoardInterpretation::AddZoneAsBase(int IdZone, const Color::ColorEnum& color)
{
	if (IdZone >= k_boardHeight * k_boardWidth || IdZone < 0)// invalid ID
		return false;
	for (auto& neighbour : m_zonesNeighbours[IdZone])
	{
		if (std::get<1>(m_board[neighbour.first]) != nullptr)
			return false;
	}
	m_board[IdZone] = { 300,std::make_shared<Color::ColorEnum>(color),true };
	m_playerBaseLifes[IdZone] = 3;
	generateNeighbours();
	return true;
}

bool BoardInterpretation::AddCloseZone(int IdZone, const Color::ColorEnum& color)
{
	if (IdZone >= k_boardHeight * k_boardWidth || IdZone < 0)// invalid ID
		return false;
	if (std::get<1>(m_board[IdZone]) != nullptr)
		return false;
	// verificare daca jucatorul are miscari valide , daca nu , poate ocupa zona curenta
	if (checkIfPlayerHasValidMoved(color))
	{
		//verificare daca un vecin este de culoare buna
		for (auto& neighbour : m_zonesNeighbours[IdZone])
		{
			if (neighbour.second.get() != nullptr && *neighbour.second.get() == color)
			{
				m_board[IdZone] = { 100, std::make_shared<Color::ColorEnum>(color),false };
				generateNeighbours();
				return true;
			}
		}
	}
	else
	{
		m_board[IdZone] = { 100 ,std::make_shared<Color::ColorEnum>(color),false };
		return true;
	}
	return false;
}

bool BoardInterpretation::checkBoardFull()
{
	for (auto& zone : m_board)
		if (std::get<1>(zone) == nullptr)
			return false;
	return true;
}

void BoardInterpretation::generateBoard(int NumberOfPlayers)
{
	if (NumberOfPlayers == 2)
	{
		k_boardHeight = 3;
		k_boardWidth = 3;
	}
	else if (NumberOfPlayers == 3)
	{
		k_boardWidth = 3; // latime
		k_boardHeight = 5; // lungime 
	}
	else {
		k_boardHeight = 6;
		k_boardWidth = 4;
	}
	m_board.resize(k_boardHeight * k_boardWidth + 1);
	m_board[k_boardHeight * k_boardWidth] = { 0,std::make_shared<Color::ColorEnum>(Color::getDefaultColor()),false };
}

void BoardInterpretation::generateNeighbours()
{
	for (int i = 0; i < k_boardHeight * k_boardWidth; i++)
	{
		if (i - k_boardWidth >= 0) // verificare prima linie
			m_zonesNeighbours[i][i - k_boardWidth] = (std::get<1>(m_board[i - k_boardWidth]));
		if (i % k_boardWidth != 0)// verificare stanga
			m_zonesNeighbours[i][i - 1] = (std::get<1>(m_board[i - 1]));
		if (i % k_boardWidth != k_boardWidth - 1) // verificare dreapta
			m_zonesNeighbours[i][i + 1] = (std::get<1>(m_board[i + 1]));
		if (i + k_boardWidth < k_boardHeight * k_boardWidth)//verificare ultima linie
			m_zonesNeighbours[i][i + k_boardWidth] = (std::get<1>(m_board[i + k_boardWidth]));
	}
}

bool BoardInterpretation::checkIfPlayerHasValidMoved(const Color::ColorEnum& color)
{
	for (int i = 0; i < k_boardHeight * k_boardWidth; i++)
	{
		auto& [score, m_color, isBase] = m_board[i];
		if (m_color != nullptr && *m_color.get() == color)
		{
			for (auto& neighbour : m_zonesNeighbours[i])
			{
				if (neighbour.second == nullptr)
					return true;
			}
		}
	}
	return false;
}
