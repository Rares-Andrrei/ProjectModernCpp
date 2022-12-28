#pragma once
#include <unordered_map>
#include <string>
#include "Account.h"
#include "Player.h"
#include <memory>
class ActivePlayers
{
	//o instanta a acestei clase va fi folosita in clasa cu rute
	std::unordered_map<std::string, std::shared_ptr<Player>> m_players;
public:
	std::string addActivePlayer(const Account& ac); //atunci cand este apelata ruta de logare si s-a facut cu succes playerului i se asociaza acel std::string unic prin care este identificat si este adaugat in map

	void logOutPlayer(std::string sessionKey); // la logOut playerul este scos din map


};