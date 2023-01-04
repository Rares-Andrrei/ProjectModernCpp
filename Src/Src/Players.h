#pragma once
#include "Account.h"
#include "Lobby.h"
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <memory>
#include "../../Player/Player/Player.h"

class Players
{
	std::unordered_map<std::string, std::shared_ptr<Player>> m_players;


public:
	//std::weak_ptr<Lobby> addPlayerToLobby(std::string sessionKey, Lobby::LobbyType lobby);

	std::shared_ptr<Player> getPlayer(const std::string& sessionKey);

	std::string addActivePlayer(const Account& ac); //atunci cand este apelata ruta de logare si s-a facut cu succes playerului i se asociaza acel std::string unic prin care este identificat si este adaugat in map
	bool isActive(const std::string& sessionKey);

	void logOutPlayer(const std::string& sessionKey); // la logOut playerul este scos din map

};