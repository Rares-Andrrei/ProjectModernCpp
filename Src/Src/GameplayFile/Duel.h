#pragma once
#include "QuestionManager.h"
#include <optional>
#include "../../Player/Player/Player.h"
#include <utility>
#include "Board.h"
#include "NumericQuestionManager.h"
#include <PlayerBase.h>

class Duel
{
public:
	enum class DuelState{
		Win,
		Lose,
		Draw,
		lifeTaken,
		None
	};
private:
	std::shared_ptr<Database> m_db;

	std::optional<Duel::DuelState> m_state;
	std::pair<Color::ColorEnum, Color::ColorEnum> m_duelingPlayers;
	std::unordered_map<Color::ColorEnum, int> m_responses;

	int m_zoneId;
	std::shared_ptr<Zone> m_zone;

	std::optional<QTypeVariants> m_qTypeVariants;

	NumericQuestionManager m_numerical;

	std::vector<std::shared_ptr<Zone>> m_updatedZones;
	Color::ColorEnum m_winner;
	bool m_draw;

	void generateQuestion();
public:
	Duel(const Color::ColorEnum& player, std::shared_ptr<Zone> zone, int zoneId, std::shared_ptr<Database> db);
	void getDuelInfo(Color::ColorEnum& c1, Color::ColorEnum& c2, int& zoneId);
	void setDuelVaraintsAnswer(Color::ColorEnum color, int variant);
	void setNumericalAnswer(int time, int response, const Color::ColorEnum& color);
	QTypeVariants getQTypeVariants();
	QTypeNumerical getQTypeNumerical();
	bool isDraw();
	Color::ColorEnum getAttacker();
	void setWinner(Board& board);
	DuelState getState();
	int getZoneId();
	std::vector<std::shared_ptr<Zone>> getUpdatedZones();
};