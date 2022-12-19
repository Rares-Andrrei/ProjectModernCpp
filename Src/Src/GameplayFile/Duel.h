#pragma once
#include "QuestionManager.h"
#include <optional>
#include "Player.h"
#include <utility>
#include <PlayerBase.h>

class Duel
{
	static const uint8_t time = 30;
	std::pair<Player::Color, Player::Color> m_duelingPlayers;
	std::shared_ptr<Zone> m_zone;
	std::optional<QTypeVariants> m_qTypeVariants;
	std::optional<QTypeNumerical> m_qTypeNumerical;
	Player::Color m_winner;
	bool m_draw;

public:
	Duel(Player::Color, std::shared_ptr<Zone> zone);
	void generateQuestion(QuestionManager& questions);
	void startDuel();

private:
	void giveAnswers(int attacker, int defender);
	void giveAnswers(std::string attacker, std::string defender);

	void giveNumericalAnswers(std::tuple<int, int, Player::Color> attacker, std::tuple<int, int, Player::Color> defender);
	void rewardWinner();
};