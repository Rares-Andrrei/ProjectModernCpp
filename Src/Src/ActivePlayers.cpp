#include "ActivePlayers.h"

std::string ActivePlayers::addActivePlayer(const Account& ac)
{
    std::string sessionKey = ac.getNickName() + ac.getUsername();
    m_players.emplace(sessionKey, std::make_shared<Player>(ac.getNickName()));
    return sessionKey;
    //pentru a stoca un player in afara clasei folosim weak_ptr si verificam mereu daca este != nullptr pentru ca aplayerul se poate deconecta si in cazul acesta devine nulltpr (se sterge cel chared din unordered_map)
}

void ActivePlayers::logOutPlayer(std::string sessionKey)
{
    m_players.erase(sessionKey);
}
