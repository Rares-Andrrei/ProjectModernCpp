#pragma once
#include <vector>
#include "../Color/Color/Color.h"

class DuelManager
{
public:
	enum class duelStatus {
		None,
		Lose,
		Draw,
		Win,
		lifeTaken
	};

private:
	duelStatus m_duelStatus;
	std::vector<std::tuple<int, Color::ColorEnum, int>> m_updatedZones;// id , color score
	std::tuple<int, int, int, Color::ColorEnum, Color::ColorEnum, Color::ColorEnum> m_duelParticipants; // id , nr_lifes  ,score , attacker & defender colors
	std::pair<Color::ColorEnum, Color::ColorEnum> m_tieBreakerParticipants;

public:
	DuelManager();
	void setDuelStatus(const DuelManager::duelStatus& duelStatus);
	void setLifeTaken(int ZoneId, int lives, int score, const Color::ColorEnum& zoneColor, const  Color::ColorEnum& attacker, const Color::ColorEnum& defender);
	void setWinChanges(const std::vector<std::tuple<int, Color::ColorEnum, int>>& updatedZones);
	void setTieBreakerParticipants(const std::pair<Color::ColorEnum, Color::ColorEnum>& players);
	duelStatus getDuelStatus();
	std::tuple<int, int, int, Color::ColorEnum, Color::ColorEnum, Color::ColorEnum> getUpdatedBase();
	std::vector<std::tuple<int, Color::ColorEnum, int>> getUpdatedZones();
	std::pair<Color::ColorEnum, Color::ColorEnum> getTieBreakerParticipants();
};