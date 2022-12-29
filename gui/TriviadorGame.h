#pragma once

#include <QMainWindow>
#include "ui_TriviadorGame.h"
#include <cstdlib>
#include <Qtime>

class TriviadorGame : public QMainWindow
{
	Q_OBJECT

public:
	TriviadorGame(QWidget *parent = nullptr);
	~TriviadorGame();

	void setNumberOfPlayers(const uint16_t& numberOfPlayers);
	
	void displayeLoadingMessage(/*const QTimer& timer*/);

	void StartGame();

private:
	uint16_t m_numberOfPlayers;
	
	Ui::TriviadorGameClass ui;
};
