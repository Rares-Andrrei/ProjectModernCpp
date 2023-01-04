#pragma once
#include <unordered_map>
#include <memory>
#include "Player.h"
#include <crow.h>
#include <stack>
class Lobby
{
public:
	static long currentCount;
	enum class LobbyType : int
	{
		TwoPlayer = 2,
		ThreePlayers = 3, //in functie de acest enum o sa fie ales si tipul hartii
		FourPlayers = 4
	};
private:
	long m_uniqueId;
	LobbyType m_type;
	std::stack<Player::Color> m_avalableColors;
	std::unordered_map<std::string, std::shared_ptr<Player>> m_players;
public:
	Lobby(LobbyType type);
	crow::json::wvalue getPlayersData();
	int playersInLobby();
	bool existInLobby(const std::string& sessionKey);
	void addPlayer(const std::string& sessionKey, std::shared_ptr<Player> player);
	void removePlayer(const std::string& sessionKey);

	static LobbyType stringToLobbyType(const std::string& string);
};