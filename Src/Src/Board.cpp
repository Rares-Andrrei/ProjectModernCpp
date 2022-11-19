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

void Board::ObtainTotalScore()
{
	m_totalScore = 0;
	for (const auto& z : m_board)
	{
		if (z.has_value())
		{
			auto zone = z.value();
			// implementare metoda GetScore in clasa Zone
			//m_totalScore = zone.GetScore();
		}
	}
}

int Board::getTotalScore()
{
	return m_totalScore;
}

std::ostream& operator<<(std::ostream& out, Board board)
{
	out << '\n';
	Board::Position pos;
	auto& [row, column] = pos;
	for ( row = 0; row < board.m_BoardHeight; row++)
	{
		for ( column = 0; column < board.m_BoardWidth; column++)
		{
			if (board[pos].has_value())
			{
				//implementare operator afisare pentru clasa ZONE
				//out << *board[pos] << ' ';
			}
			else {
				out << "________ ";
			}
		}
	}
	return out;
}
