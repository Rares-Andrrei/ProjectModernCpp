#pragma once

#include <QMainWindow>
#include <memory>
#include "ui_TriviadorGame.h"
#include <cstdlib>
#include <Qtime>
#include "PlayerQString.h"
#include "Route.h"

#include "Map.h"
#include "QTypeNumericWindow.h"
#include "QTypeVariantsWindow.h"

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
	enum class GamePhase
	{
		None,
		ChooseBase,
		ChooseRegions,
		Duels,
		End
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
	void startDuel();

	void EndGame();

	void displayPodium();

	void checkNumericWindowClosed();
	void checkMapWindowClosed();
	void checkVariantsWindowClosed();
	void checkCurrentPhase();

	bool checkIfWindowsAreClosed();

private:
	std::shared_ptr<Route> m_GameInstance;
	uint16_t m_numberOfPlayers;
	std::shared_ptr<PlayerQString>m_player;
	std::vector<std::shared_ptr<PlayerQString>>m_players;

	GamePhase m_gamePhase : 3 = GamePhase::None;
	DuelStatus m_duelStatus : 3 = DuelStatus::None;

	bool serverAproveStatus = true;
	bool changePhase = true;
	bool m_MapWindowClosed = false;
	bool m_VariantsWindowClosed = false;
	bool duelFinished = false;

	int m_numberOfDuels = 0;
	int m_MaxNumberOfDuels = 0;

	std::unique_ptr<QTimer> t_MapWindowTimer;
	std::unique_ptr<QTimer> t_NumericWindowTimer;
	std::unique_ptr<QTimer> t_VariantsWindowTimer;
	std::unique_ptr<QTimer> t_checkCurrentPhase;

	Ui::TriviadorGameClass ui;

	std::shared_ptr<QTypeNumericWindow> m_QTypeNumericWindow;
	std::shared_ptr<QTypeVariantsWindow> m_QTypeVariantsWindow;
	std::unique_ptr<Map> MapWindow;
};
