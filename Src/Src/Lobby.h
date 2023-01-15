#pragma once
#include <unordered_map>
#include <memory>
#include <crow.h>
#include <stack>
#include <sstream>
#include "../../Player/Player/Player.h"

class Lobby
{
public:
	static long currentCount;
	enum class LobbyType : int
	{
		TwoPlayer = 2,
		ThreePlayers = 3,
		FourPlayers = 4
	};
private:
	long m_uniqueId;
	LobbyType m_type;
	std::stack < Color::ColorEnum > m_avalableColors;
	std::unordered_map<std::string, std::shared_ptr<Player>> m_players;
public:
	Lobby(LobbyType type);
	long getId();
	LobbyType getType();
	crow::json::wvalue getPlayersData();
	std::vector<std::shared_ptr<Player>> getPlayers();
	int playersInLobby();
	bool existInLobby(const std::string& sessionKey);
	void addPlayer(const std::string& sessionKey, std::shared_ptr<Player> player);
	void removePlayer(const std::string& sessionKey);

	static LobbyType stringToLobbyType(const std::string& string);
};