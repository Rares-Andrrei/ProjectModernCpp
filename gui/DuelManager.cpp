#include "DuelManager.h"

DuelManager::DuelManager()
	:m_duelStatus{ DuelManager::duelStatus::None }
{
}

void DuelManager::setDuelStatus(const DuelManager::duelStatus& duelStatus)
{
	m_duelStatus = duelStatus;
}

void DuelManager::setLifeTaken(int ZoneId, int lives, int score, const Color::ColorEnum& attacker, const Color::ColorEnum& defender)
{
	std::make_tuple(ZoneId, lives, score, attacker, defender);
}

void DuelManager::setWinChanges(const std::vector<std::tuple<int, Color::ColorEnum, int>>& updatedZones)
{
	m_updatedZones = updatedZones;
}

DuelManager::duelStatus DuelManager::getDuelStatus()
{
	return m_duelStatus;
}

std::tuple<int, int, int, Color::ColorEnum, Color::ColorEnum> DuelManager::getUpdatedBase()
{
	return m_duelParticipants;
}

std::vector<std::tuple<int, Color::ColorEnum, int>> DuelManager::getUpdatedZones()
{
	return m_updatedZones;
}
