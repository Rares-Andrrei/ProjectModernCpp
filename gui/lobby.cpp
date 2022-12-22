#include "lobby.h"

lobby::lobby(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	MapWindow.reset(new Map());
	ui.twoPlayersButton->setStyleSheet("Text-align:left, up");
	ui.threePlayersButton->setStyleSheet("Text-align:left, up");
	ui.fourPlayersButton->setStyleSheet("Text-align:left, up");
	connect(ui.twoPlayersButton, SIGNAL(clicked()), SLOT(ontwoPlayersButtonClicked()));
}

lobby::~lobby()
{
	
}
void lobby::ontwoPlayersButtonClicked()
{
	MapWindow->show();
}
