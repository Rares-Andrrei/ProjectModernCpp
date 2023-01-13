#pragma once
#include "Zone.h"
#include "PlayerBase.h"
#include <optional>
#include <vector>
#include <memory>
#include <unordered_map>
#include <iostream>
class Board
{
	uint8_t m_NumberOfPlayers; // Numarul maxim de jucatori este 4
	uint8_t m_BoardWidth;
	uint8_t m_BoardHeight;
	std::vector<std::shared_ptr<Zone>> m_board;
	std::unordered_map<int, std::unordered_map<int, std::shared_ptr<Zone>>> m_zonesNeighbours;
	int m_totalScore;
	int m_modifiedZones;

public:
	Board(const uint8_t& NumberOfPlayers = 2);

	using Position = std::pair<int, int>;

	friend std::ostream& operator <<(std::ostream& out, const Board& board);

	const std::shared_ptr<Zone>& operator[](const Position& indices) const;
	std::shared_ptr<Zone>& operator[](const Position& indices);
	std::shared_ptr<Zone>& operator[](int id);


	bool ValidateBasePosition(int idZone);
	bool ValidateRegionPosition(int idZone, const Color::ColorEnum& color);
	bool AddZonaAsBase(int idZone, const Color::ColorEnum& color);
	bool AddCloseZone(int idZone, const Color::ColorEnum& color);
	bool ValidateAttackMove(int idZone, const Color::ColorEnum& color);


	void incrementModifiedZones();
	int getModifiedZones();
	void ObtainTotalScore();
	int getTotalScore();
	uint8_t getNumberOfPlayers();
	bool CheckIfBoardIsFull();
	void eliminatePlayer(const Color::ColorEnum& elimated, const Color::ColorEnum& newOwner);
	std::shared_ptr<Zone>& end();

private:
	void ChangeBoardDimensions();
	void generateNeighbours();
	bool checkIfPlayerHasValidMoved(const Color::ColorEnum& color);
};