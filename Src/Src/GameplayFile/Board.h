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
	uint8_t m_NumberOfPlayers;
	uint8_t m_BoardWidth;
	uint8_t m_BoardHeight;
	std::vector<std::shared_ptr<Zone>> m_board;
	std::unordered_map<int, std::unordered_map<int, std::shared_ptr<Zone>>> m_zonesNeighbours;
	int m_totalScore;
	int m_modifiedZones;

public:
	using Position = std::pair<int, int>;

	Board(const uint8_t& NumberOfPlayers = 2);

	const std::shared_ptr<Zone>& operator[](const Position& indices) const;
	std::shared_ptr<Zone>& operator[](const Position& indices);
	std::shared_ptr<Zone>& operator[](int id);

	bool ValidateBasePosition(int idZone);
	bool ValidateRegionPosition(int idZone, const Color::ColorEnum& color);
	bool AddZonaAsBase(int idZone, const Color::ColorEnum& color);
	bool AddCloseZone(int idZone, const Color::ColorEnum& color);
	bool ValidateAttackMove(int idZone, const Color::ColorEnum& color);
	bool checkIfPlayerCanUseAdvantages(const Color::ColorEnum& color);

	std::tuple<int, Color::ColorEnum, int, int> getZoneInfo(int idZone);

	void incrementModifiedZones();
	int getModifiedZones();
	void ObtainTotalScore();
	int getTotalScore();
	uint8_t getNumberOfPlayers();
	bool CheckIfBoardIsFull();
	void eliminatePlayer(const Color::ColorEnum& elimated, const Color::ColorEnum& newOwner);
	std::shared_ptr<Zone>& end();
	void generateNeighbours();

	int getPlayerScore(const Color::ColorEnum& color);

private:
	void ChangeBoardDimensions();
	bool checkIfPlayerHasValidMoved(const Color::ColorEnum& color);
};