#include "Players.h"


std::shared_ptr<Player> Players::getPlayer(const std::string& sessionKey)
{
    return m_players[sessionKey];
}

std::string Players::addActivePlayer(const Account& ac)
{
    std::string sessionKey = ac.getNickName() + ac.getUsername();
    m_players.emplace(sessionKey, std::make_shared<Player>(ac.getNickName().c_str()));
    return sessionKey;
    //pentru a stoca un player in afara clasei folosim weak_ptr si verificam mereu daca este != nullptr pentru ca aplayerul se poate deconecta si in cazul acesta devine nulltpr (se sterge cel shared din unordered_map)
}

bool Players::isActive(const std::string& sessionKey)
{
    return m_players.count(sessionKey) > 0;
}


void Players::logOutPlayer(const std::string& sessionKey)
{
    m_players.erase(sessionKey);
}