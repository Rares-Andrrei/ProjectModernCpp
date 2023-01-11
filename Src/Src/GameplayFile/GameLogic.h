#pragma once
#include "Board.h"
#include <crow.h>
#include "QuestionManager.h"
#include "../../Player/Player/Player.h"
#include  "Advantages.h"
#include "ChooseBase.h"
#include "Duel.h"
#include "NumericQuestionManager.h"

class GameLogic
{
	Board m_board;

	QuestionManager m_questions;

	QTypeVariants m_questionTypeVariants;

	NumericQuestionManager m_numericQuestionManager;

	std::vector<std::shared_ptr<Player>> m_winners;

	const uint16_t k_numberOfPlayers;
	std::vector<std::shared_ptr<Player>> m_players;
	std::vector<std::shared_ptr<Player>> m_eliminatedPlayers;
	std::optional<std::pair<int, Color::ColorEnum>> m_updatedZone; //sa se stearga dupa ce toti playerii au updatat zona
	//std::vector<std::shared_ptr<Advantages>> m_advantages; // de vazut unde sa fie folosit . 

	std::shared_ptr<Database> m_db;
	void randomQTypeNumerical();
	void randomQTypeVariants();

	int NumberOfRequests = 0;
public:
	GameLogic();
	GameLogic(const uint16_t& numberOfPlayers, std::shared_ptr<Database> db);
	//GameLogic(const GameLogic&) = delete;
	//GameLogic(GameLogic&&) = delete;
	//GameLogic& operator=(const GameLogic&) = delete;
	//GameLogic& operator=(GameLogic&&) = delete;

	bool checkZoneUpdates();
	std::pair<int, Color::ColorEnum> getUpdatedZone();
	void updateZone(int zoneId, Color::ColorEnum zoneColor);
	void eraseUpdatedZone(); //se apeleaza atuncic and se genereaza o noua intrebare (inseamna ca toti layerii au updatat zona si s-a trecut mai deprarte
public:
	bool NumberOfRequestsReached();
	void increaseNumberOfRequest();

	static crow::json::wvalue playersToJson(std::vector < std::shared_ptr<Player>> players);
	QTypeNumerical getQuestionTypeNumerical();
	QTypeVariants getQuestionTypeVariants();
	void setPlayerNumericalAnswer(int time, int response, const Color::ColorEnum& color);
	bool NumericalAnswersReady();
	std::vector<std::shared_ptr<Player>> getWinnerList();



	void StartGame();
	void EndGame();
	void addPlayer(std::shared_ptr<Player> player);

	~GameLogic() = default;
private:

	void phases();
	void chooseBasePhase();
	void chooseRegionsPhase();
	void duelsPhase();
	bool checkIfPlayerWasEliminated(std::shared_ptr<PlayerBase>& playerBase);
};

