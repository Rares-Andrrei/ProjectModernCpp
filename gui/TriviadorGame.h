#pragma once

#include <QMainWindow>
#include <memory>
#include "ui_TriviadorGame.h"
#include "Map.h"
#include <cstdlib>
#include <Qtime>

class TriviadorGame : public QMainWindow
{
	Q_OBJECT

public:
	enum class DuelStatus
	{
		Lose,
		Win,
		Draw
	};
	TriviadorGame(QWidget* parent = nullptr);
	~TriviadorGame();

	void setNumberOfPlayers(const uint16_t& numberOfPlayers);

	void displayLoadingMessage(/*const QTimer& timer*/);

	void StartGame();

private:
	void chooseBasePhase();

	void chooseRegionsPhase();

	void duelsPhase();

	void EndGame();

	void displayPodium();

private:
	uint16_t m_numberOfPlayers;

	Ui::TriviadorGameClass ui;
	std::unique_ptr<Map> MapWindow;
};
