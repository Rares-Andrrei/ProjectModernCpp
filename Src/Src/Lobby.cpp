#include "Lobby.h"
#include <sstream>


Lobby::LobbyType Lobby::getType()
{
	return m_type;
}

long Lobby::getId()
{
	return m_uniqueId;
}

int Lobby::playersInLobby()
{
	return m_players.size();
}

std::vector<std::shared_ptr<Player>> Lobby::getPlayers()
{
	std::vector<std::shared_ptr<Player>> players;
	for (auto player : m_players)
	{
		players.push_back(player.second);
	}
	return players;
}

void Lobby::addPlayer(const std::string& sessionKey, std::shared_ptr<Player> player)
{
	player->setColor(m_avalableColors.top());
	m_avalableColors.pop();
	m_players.emplace(sessionKey, player);
}

Lobby::Lobby(LobbyType type) : m_type{ type }, m_avalableColors{ {Color::ColorEnum::Blue, Color::ColorEnum::Green, Color::ColorEnum::Red, Color::ColorEnum::Yellow} }, m_uniqueId{currentCount++}
{
}

Lobby::LobbyType Lobby::stringToLobbyType(const std::string& string)
{
	std::stringstream ss(string);
	int lobbyNr;
	ss >> lobbyNr;
	switch (lobbyNr)
	{
	case (2):
		return LobbyType::TwoPlayer;
		break;
	case (3):
		return LobbyType::ThreePlayers;
		break;
	case(4):
		return LobbyType::FourPlayers;
		break;
	}
}

bool Lobby::existInLobby(const std::string& sessionKey)
{
	return m_players.count(sessionKey) > 0;
}

void Lobby::removePlayer(const std::string& sessionKey)
{
	m_avalableColors.push(m_players[sessionKey]->getColor());
	m_players[sessionKey]->setColor(Color::ColorEnum::None);
	m_players.erase(sessionKey);

}

crow::json::wvalue Lobby::getPlayersData()
{
	crow::json::wvalue json;
	int playerNr = 1;
	json["lobbyID"] = m_uniqueId;
	for (const auto& p : m_players)
	{
		json["playerName" + std::to_string(playerNr)] = p.second->getName();
		json["playerColor" + std::to_string(playerNr)] = Color::ColorToString(p.second->getColor());
		json["playerScore" + std::to_string(playerNr)] = p.second->getScore();
		playerNr++;
	}
	return json;
}
