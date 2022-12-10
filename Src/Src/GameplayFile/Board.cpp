#include "Board.h"

Board::Board(const uint8_t NumberOfPlayers)
	:m_NumberOfPlayers{ NumberOfPlayers }
{
	this->ChangeBoardDimensions();
}

void Board::ChangeBoardDimensions()
{
	if (this->m_NumberOfPlayers > 4)
	{
		std::string message = "So much players, sorry I'm crashed :(";
		try
		{
			throw(message);
		}
		catch (std::string message)
		{
			std::cout << std::endl;
			std::cerr << message;
			return;

		}
	}
	else
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
		m_board.resize(m_BoardHeight * m_BoardWidth);// fill board with empty (Zones)

	}
}

const std::shared_ptr<Zone>& Board::operator[](const Position& indices) const
{
	const auto& [row, column] = indices;
	return m_board[row * m_BoardWidth + column];
}

std::shared_ptr<Zone>& Board::operator[](const Position& indices)
{
	const auto& [row, column] = indices;
	return m_board[row * m_BoardWidth + column];
}

void Board::ObtainTotalScore()
{
	m_totalScore = 0;
	for (const auto& z : m_board)
	{
		if (z!= nullptr)
		{
			m_totalScore += z->getScore();
		}
	}
}

int Board::getTotalScore()
{
	return m_totalScore;
}

uint8_t Board::getNumberOfPlayers()
{
	return m_NumberOfPlayers;
}

std::ostream& operator<<(std::ostream& out, Board board)
{
	out << '\n';
	Board::Position pos;
	auto& [row, column] = pos;
	for (row = 0; row < board.m_BoardHeight; row++)
	{
		for (column = 0; column < board.m_BoardWidth; column++)
		{
			if (board[pos]!= nullptr)
			{
				out << *board[pos] << ' ';

				/*auto current = board[pos];

				auto d_ptr = std::static_pointer_cast<PlayerBase>(current);
				out << d_ptr << ' ';*/
			}
			else {
				out << "________ ";
			}
		}
		out << std::endl;
	}
	return out;
}