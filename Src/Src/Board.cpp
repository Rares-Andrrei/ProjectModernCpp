#include "Board.h"

Board::Board(const uint8_t NumberOfPlayers)
	:m_NumberOfPlayers{ NumberOfPlayers }
{
	this->ChangeBoardDimensions();
}

void Board::ChangeBoardDimensions()
{
	if (this->m_NumberOfPlayers == 2)
	{
		this->m_BoardHeight = 3;
		this->m_BoardWidth = 3;
	}
	else if (this->m_NumberOfPlayers == 3)
	{
		this->m_BoardHeight = 3;
		this->m_BoardWidth = 5;
	}
	else {
		this->m_BoardHeight = 4;
		this->m_BoardWidth = 6;
	}
	m_board.resize(m_BoardHeight * m_BoardWidth);

}

const std::optional<Zone>& Board::operator[](const Position& indices) const
{
	const auto& [row, column] = indices;
	return m_board[row * m_BoardWidth + column];
}

std::optional<Zone>& Board::operator[](const Position& indices)
{
	const auto& [row, column] = indices;
	return m_board[row * m_BoardWidth + column];
}

int Board::getTotalScore()
{
	return m_totalScore;
}

