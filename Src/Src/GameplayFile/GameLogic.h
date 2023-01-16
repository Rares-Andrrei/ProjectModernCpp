#pragma once
#include "Board.h"
#include <crow.h>
#include "QuestionManager.h"
#include "../../Player/Player/Player.h"
#include  "Advantages.h"
#include "Duel.h"
#include "NumericQuestionManager.h"
#include <random>
#include <algorithm>

class GameLogic
{
	Board m_board;
	QuestionManager m_questions;
	NumericQuestionManager m_numericQuestionManager;
	std::optional<Duel> m_duel;
	std::vector<std::shared_ptr<Player>> m_winners;

	const uint16_t k_numberOfPlayers;
	std::vector<std::shared_ptr<Player>> m_players;
	std::vector<std::shared_ptr<Player>> m_eliminatedPlayers;
	std::shared_ptr<Database> m_db;
	void randomQTypeNumerical();

	Color::ColorEnum m_colorToAttack;
	std::queue<Color::ColorEnum> m_duelOrder;
	std::optional<std::pair<int, Color::ColorEnum>> m_updatedZone;
	std::unordered_map<Color::ColorEnum, bool> m_requests;

public:
	void setDuel(Color::ColorEnum attacker, int regionId);
	void getDuelingPlayersAndZone(Color::ColorEnum& c1, Color::ColorEnum& c2, int& zoneid);
	void createDuelOrder();
	int getDuelZoneId();
	int getZoneId(std::shared_ptr<Zone> zone);
	void duelPlayerResponse(Color::ColorEnum color, int variant);
	void setColorToAttack();
	void setDuelNumericalAnswer(int time, int response, const Color::ColorEnum& color);
	Color::ColorEnum currentDuelAttacker();
	QTypeNumerical getDuelNumericalQ();
	void deleteColorToAttack();
	std::vector<std::shared_ptr<Zone>> getDuelZones();
	Duel::DuelState getDuelState();
	void setDuelPlayerWinner();
	bool duelDraw();
	Color::ColorEnum getAttackerColor();
	std::pair<int, int> taxForAdvantage(Color::ColorEnum color);

	void addWaitingRequest(const Color::ColorEnum& sessionKey);
	bool allRequestsReady();
	void deleteRequestsReady();

	bool ValidateBasePosition(int idZone);
	bool ValidateRegionPosition(int idZone, const Color::ColorEnum& color);
	bool ValidateAttackMove(int idZone, const Color::ColorEnum& color);
	bool CheckIfBoardIsFull();
	bool checkIfPlayerCanUseAdvantages(const Color::ColorEnum& color);
	std::tuple<int, Color::ColorEnum, int, int> getZoneInfo(int idZone);

	GameLogic();
	GameLogic(const uint16_t& numberOfPlayers, std::shared_ptr<Database> db);

	bool checkZoneUpdates();
	std::pair<int, Color::ColorEnum> getUpdatedZone();
	void updateZone(int zoneId, Color::ColorEnum zoneColor);
	void eraseUpdatedZone();
public:
	static crow::json::wvalue playersToJson(std::vector < std::shared_ptr<Player>> players);
	QTypeNumerical getQuestionTypeNumerical();
	QTypeVariants getQuestionTypeVariants();
	void setPlayerNumericalAnswer(int time, int response, const Color::ColorEnum& color);
	bool NumericalAnswersReady();
	std::vector<std::shared_ptr<Player>> getWinnerList();
	std::vector<std::shared_ptr<Player>> getPlayers();
	void updatePlayersScores();
	void addPlayer(std::shared_ptr<Player> player);

	~GameLogic() = default;
private:
	bool checkIfPlayerWasEliminated(std::shared_ptr<PlayerBase>& playerBase);
};

