#include "lobby.h"

lobby::lobby(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.twoPlayersButton->setStyleSheet("Text-align:left, up");
	ui.threePlayersButton->setStyleSheet("Text-align:left, up");
	ui.fourPlayersButton->setStyleSheet("Text-align:left, up");
}

lobby::~lobby()
{}
