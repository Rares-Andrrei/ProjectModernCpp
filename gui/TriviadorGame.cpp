#include "TriviadorGame.h"

TriviadorGame::TriviadorGame(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

TriviadorGame::~TriviadorGame()
{}

void TriviadorGame::setNumberOfPlayers(const uint16_t & numberOfPlayers)
{
	m_numberOfPlayers = numberOfPlayers;
}

void TriviadorGame::displayeLoadingMessage(/*const QTimer& timer*/)
{
	// afisare loading screen , parametrizat
}

void TriviadorGame::StartGame()
{
	// afisare loading screen
	// Etape :
	//		alegere baza
	// 		alegere regiuni
	//		dueluri
	// 
	// Endgame
	// afisare loagind screen
	// afisare rezultate
	// 
	// Aducerea jucatorilor inaloi la lobby
	// afisare loading screen
}
