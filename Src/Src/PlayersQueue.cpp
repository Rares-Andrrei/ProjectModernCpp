#include "PlayersQueue.h"


PlayersQueue::PlayersQueue()
{

}

std::shared_ptr<Lobby> PlayersQueue::addPlayerToLobby(std::string sessionKey, Lobby::LobbyType lobby)
{
    if (m_lobbies.count(lobby) > 0 && m_lobbies[lobby]->playersInLobby() < static_cast<int>(lobby))
    {
        m_lobbies[lobby]->addPlayer(sessionKey, m_players[sessionKey]);
    }
    else
    {
        m_lobbies.emplace(lobby, std::make_shared<Lobby>(lobby));
        m_lobbies[lobby]->addPlayer(sessionKey, m_players[sessionKey]);
    }

    return m_lobbies[lobby];
}

void PlayersQueue::kickPlayerFromLobby(const std::string& sessionKey)
{
    for (auto& lobby: m_lobbies)
    {
        if (lobby.second->existInLobby(sessionKey))
        {
            lobby.second->removePlayer(sessionKey);
            return;
        }
    }
}

std::shared_ptr<Player> PlayersQueue::getPlayer(const std::string& sessionKey)
{
    return m_players[sessionKey];
}

std::string PlayersQueue::addActivePlayer(const Account& ac)
{
    std::string sessionKey = ac.getNickName() + ac.getUsername();
    m_players.emplace(sessionKey, std::make_shared<Player>(ac.getNickName()));
    return sessionKey;
}

bool PlayersQueue::isActive(const std::string& sessionKey)
{
    return m_players.count(sessionKey) > 0;
}


void PlayersQueue::logOutPlayer(const std::string& sessionKey)
{
    m_players.erase(sessionKey);
}