#include "Board.h"

Board::Board(const uint8_t& NumberOfPlayers)
<<<<<<< Updated upstream
	:m_NumberOfPlayers{ NumberOfPlayers }
=======
	:m_NumberOfPlayers{ NumberOfPlayers }, m_modifiedZones{ 0 }
>>>>>>> Stashed changes
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
		m_board.resize(m_BoardHeight * m_BoardWidth + 1);// fill board with empty (Zones)
		m_board[m_BoardHeight * m_BoardWidth] = std::make_shared<Zone>(Color::getDefaultColor());// default value for board
		this->generateNeighbours();
	}
}

void Board::generateNeighbours()
{
	for (int i = 0; i < m_BoardHeight * m_BoardWidth; i++)
	{
		if (i - m_BoardWidth >= 0) // up
			m_zonesNeighbours[i][i - m_BoardWidth] = m_board[i - m_BoardWidth];
		if (i + m_BoardWidth < m_BoardHeight * m_BoardWidth)//  down
			m_zonesNeighbours[i][i + m_BoardWidth] = m_board[i + m_BoardWidth];
		if (i % m_BoardWidth != 0)//  left
			m_zonesNeighbours[i][i - 1] = m_board[i - 1];
		if (i % m_BoardWidth != m_BoardWidth - 1)// right
			m_zonesNeighbours[i][i + 1] = m_board[i + 1];
	}
}

bool Board::checkIfPlayerHasValidMoved(const Color::ColorEnum& color)
{
	for (int i = 0; i < m_BoardHeight * m_BoardWidth; i++)
	{
		if (m_board[i] != nullptr && m_board[i]->getColor() == color)
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

const std::shared_ptr<Zone>& Board::operator[](const Position& indices) const
{
	const auto& [row, column] = indices;
	if (row > m_BoardHeight || row < 0 || column < 0 || column > m_BoardWidth)
	{
		return m_board[m_BoardHeight * m_BoardWidth];
	}
	return m_board[row * m_BoardWidth + column];
}


std::shared_ptr<Zone>& Board::operator[](const Position& indices)
{
	const auto& [row, column] = indices;
	if (row >= m_BoardHeight || row < 0 || column < 0 || column >= m_BoardWidth)
	{
		return m_board[m_BoardHeight * m_BoardWidth];
	}
	return m_board[row * m_BoardWidth + column];
}

std::shared_ptr<Zone>& Board::operator[](int id)
{
	if (id > m_board.size() - 1)
	{
		return m_board[m_board.size() - 1];
	}
	else if (id < 0)
	{
		return m_board[m_board.size() - 1];
	}
	else
	{
		return m_board[id];
	}
}

bool Board::ValidateBasePosition(int idZone)
{
	if (idZone >= m_BoardHeight * m_BoardWidth || idZone < 0 || m_board[idZone] != nullptr)
	{
		return false;
	}
	for (auto& neighbour : m_zonesNeighbours[idZone])
	{
		if (m_board[neighbour.first] != nullptr)
		{
			return false;
		}
	}
}

bool Board::ValidateRegionPosition(int idZone, const Color::ColorEnum& color)
{
	if (idZone >= m_BoardHeight * m_BoardWidth || idZone < 0 || m_board[idZone] != nullptr)
	{
		return false;
	}
	if (checkIfPlayerHasValidMoved(color))
	{
		for (auto& neighbour : m_zonesNeighbours[idZone])
		{
			if (neighbour.second != nullptr && neighbour.second->getColor() == color)
			{
				return true;
			}
		}
	}
	else {
		return true;
	}
	return false;
}

bool Board::AddZonaAsBase(int idZone, const Color::ColorEnum& color)
{
	if (!ValidateBasePosition(idZone))
		return false;
	m_board[idZone] = std::make_shared<PlayerBase>(PlayerBase(color));
	generateNeighbours();
	return true;
}

bool Board::AddCloseZone(int idZone, const Color::ColorEnum& color)
{
	if (!ValidateRegionPosition(idZone, color))
		return false;
	m_board[idZone] = std::make_shared<Zone>(Zone(color));
	generateNeighbours();
	return true;
}

bool Board::ValidateAttackMove(int idZone, const Color::ColorEnum& color)
{
	if (idZone >= m_BoardHeight * m_BoardWidth || idZone < 0)
	{
		return false;
	}
	if (CheckIfBoardIsFull() == true)
	{
		if (m_board[idZone]->getColor() != color)
		{
			for (auto& neighbour : m_zonesNeighbours[idZone])
			{
				if (neighbour.second->getColor() == color)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Board::ObtainTotalScore()
{
	m_totalScore = 0;
	for (const auto& z : m_board)
	{
		if (z != nullptr)
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

bool Board::CheckIfBoardIsFull()
{
	for (uint16_t index = 0; index < m_board.size() - 1; index++)
	{
		if (m_board[index] == nullptr)
		{
			return false;
		}
	}
	return true;
}

void Board::eliminatePlayer(const Color::ColorEnum& elimated, const Color::ColorEnum& newOwner)
{
	for (auto& zone : m_board)
	{
		if (zone->getColor() == elimated)
		{
			zone->changeOwner(newOwner);
		}
	}
}

std::shared_ptr<Zone>& Board::end()
{
	return m_board[m_BoardHeight * m_BoardWidth];
}

std::ostream& operator<<(std::ostream& out, const Board& board)
{
	out << '\n';
	//Board::Position pos;
	//auto& [row, column] = pos;
	for (int row = 0; row < board.m_BoardHeight; row++)
	{
		for (int column = 0; column < board.m_BoardWidth; column++)
		{
			if (board.m_board[row * board.m_BoardWidth + column] != nullptr)
			{
				out << *board.m_board[row * board.m_BoardWidth + column] << ' ';
			}
			else {
				out << "________ ";
			}
		}
		out << std::endl;
	}
	return out;
}