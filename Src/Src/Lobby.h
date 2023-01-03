#pragma once
#include <unordered_map>
#include <memory>
#include "Player.h"
class Lobby
{
public:
	enum class LobbyType : int
	{
		TwoPlayer = 2,
		ThreePlayers = 3, //in functie de acest enum o sa fie ales si tipul hartii
		FourPlayers = 4
	};
private:
	LobbyType m_type;
	std::unordered_map<std::string, std::weak_ptr<Player>> m_players;
public:
	int playersInLobby();
	bool addPlayer();
};