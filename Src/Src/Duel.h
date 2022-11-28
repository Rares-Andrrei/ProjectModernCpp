#pragma once
#include "QuestionManager.h"
#include <optional>
#include "Player.h"
#include <utility>
#include "Zone.h"
#include "QTypeNumerical.h"
#include "QTypeVariants.h"
class Duel
{
	static const uint8_t maxPlayerNumber = 4;
	static const uint8_t time = 30;
	std::pair<Player::Color, Player::Color> m_duelingPlayers;
	std::shared_ptr<Zone> m_zone;
	std::optional<QTypeVariants> m_qTypeVariants;
	std::optional<QTypeNumerical> m_qTypeNumerical;
	Player::Color m_winner;
	bool m_draw;

public:
	bool isDraw() const;

	Duel(Player::Color, std::shared_ptr<Zone> zone);

	void generateQuestion(QuestionManager& questions);

	QTypeVariants getQTypeVariants();

	QTypeNumerical getQTypeNumerical();

	void giveAnswers(int attacker, int defender);

	void giveAnswers(std::string attacker, std::string defender);

	Player::Color getWinner();
	void rewardWinner();
};