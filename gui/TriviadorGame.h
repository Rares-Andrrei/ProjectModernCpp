#pragma once

#include <QMainWindow>
#include <memory>
#include "ui_TriviadorGame.h"
#include <cstdlib>
#include <Qtime>
#include "PlayerQString.h"
#include "Route.h"
#include"MapForThreePlayers.h"
#include "Map.h"
#include "QTypeNumericWindow.h"
#include "QTypeVariantsWindow.h"
#include <qrandom.h>
#include "GamePhaseEnum.h"

class TriviadorGame : public QMainWindow
{
	Q_OBJECT

public:
	enum class DuelStatus
	{
		None,
		Lose,
		Win,
		Draw
	};
	TriviadorGame(QWidget* parent = nullptr);
	~TriviadorGame();

	void setNumberOfPlayers(const uint16_t& numberOfPlayers);

	void displayLoadingMessage(/*const QTimer& timer*/);

	void StartGame();

	void setPlayer(const std::shared_ptr<PlayerQString>& player);
	void setPlayers(const std::vector<std::shared_ptr<PlayerQString>>& players);
	void setGameInstance(const std::shared_ptr<Route>& GameInstance);
protected:
	void showEvent(QShowEvent* event) override;

private:
	void chooseBasePhase();

	void chooseRegionsPhase();

	void duelsPhase();
	//void startDuel();

	void EndGame();

	void displayPodium();

	void checkNumericWindowClosed();
	//void checkMapWindowClosed();
	void checkVariantsWindowClosed();
	void checkCurrentPhase();

	bool checkIfWindowsAreClosed();

public slots:
	void getDuelStatus(DuelManager& duelStatus);
	void getTieBreakerDuelStatus(DuelManager& duelStatus);
	void duelParticipants(const std::pair<Color::ColorEnum, Color::ColorEnum>& duelParticipants);
	void tieBreakerRound(const std::pair<Color::ColorEnum, Color::ColorEnum>& duelParticipants);
	void getTieBreakerResults(const std::vector<std::tuple<int, Color::ColorEnum, int, int>>& UpdatedZones, const std::vector<std::pair<int, Color::ColorEnum>>& updatedPlayers);
	void onSendOrderToParent(const std::queue<std::pair<Color::ColorEnum, int>>& playerOrder);
	void nextPlayerInQueue();
	void updateTheQueueStatus();
	void startNextDuel();
	void getUpdatedZonesAfterWin(const std::vector<std::tuple<int, Color::ColorEnum, int>>& updatedZones);

private:
	std::queue<std::pair<Color::ColorEnum, int>> m_playerOrder;
	std::shared_ptr<Route> m_GameInstance;
	uint16_t m_numberOfPlayers;
	std::shared_ptr<PlayerQString>m_player;
	std::vector<std::shared_ptr<PlayerQString>>m_players;
	std::shared_ptr<BoardInterpretation> m_board;

	GamePhase m_gamePhase : 3 = GamePhase::None;
	DuelStatus m_duelStatus : 3 = DuelStatus::None;

	bool serverAproveStatus = true;
	bool changePhase = true;
	bool m_MapWindowClosed = false;
	bool m_VariantsWindowClosed = false;
	bool duelFinished = false;

	int m_numberOfDuels = 0;
	int m_MaxNumberOfDuels = 0;

	int m_numberOfInteractionsLeft;

	std::unique_ptr<QTimer> t_MapWindowTimer;
	std::unique_ptr<QTimer> t_NumericWindowTimer;
	std::unique_ptr<QTimer> t_VariantsWindowTimer;
	std::unique_ptr<QTimer> t_checkCurrentPhase;

	Ui::TriviadorGameClass ui;

	std::shared_ptr<QTypeNumericWindow> m_QTypeNumericWindow;
	std::shared_ptr<QTypeVariantsWindow> m_QTypeVariantsWindow;
	std::unique_ptr<Map> MapWindow;
	//std::unique_ptr<MapForThreePlayers> MapWindow;
};
