#pragma once
#include "QuestionManager.h"
#include <optional>
#include "../../Player/Player/Player.h"
#include <utility>
#include <PlayerBase.h>

class Duel
{
	static const uint8_t time = 30;
	std::pair<Color::ColorEnum, Color::ColorEnum> m_duelingPlayers;
	std::shared_ptr<Zone> m_zone;
	std::optional<QTypeVariants> m_qTypeVariants;
	std::optional<QTypeNumerical> m_qTypeNumerical;
	Color::ColorEnum m_winner;
	bool m_draw;

public:
	Duel(const Color::ColorEnum& player, std::shared_ptr<Zone> zone);
	void generateQuestion(QuestionManager& questions);
	void startDuel();

private:
	void giveAnswers(int attacker, int defender);
	void giveAnswers(std::string attacker, std::string defender);

	void giveNumericalAnswers(std::tuple<int, int, Color::ColorEnum> attacker, std::tuple<int, int, Color::ColorEnum> defender);
	void rewardWinner();
};