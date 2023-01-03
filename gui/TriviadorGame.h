#pragma once

#include <QMainWindow>
#include <memory>
#include "ui_TriviadorGame.h"
#include <cstdlib>
#include <Qtime>

#include "Map.h"

#include "QTypeNumericWindow.h"
#include "QTypeVariantsWindow.h"

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

	void checkNumericWindowClosed();

private:
	uint16_t m_numberOfPlayers;

	Ui::TriviadorGameClass ui;
	std::shared_ptr<QTypeNumericWindow> m_QTypeNumericWindow;
	std::shared_ptr<QTypeVariantsWindow> m_QTypeVariantsWindow;
	std::unique_ptr<Map> MapWindow;
};
