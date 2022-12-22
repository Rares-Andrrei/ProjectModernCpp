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

void lobby::setPlayer(PlayerInstance player)
{
	this->Player = player;
}

lobby::~lobby()
{
	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/logout" },
		cpr::Payload{
			{ "username", Player.getFirstName()},
		}
	);

	if (response.status_code == 200 || response.status_code == 202) {
		QMessageBox::information(this, "Logout", "U have been logged out");


		QApplication::closeAllWindows();
	}
	else {
		QMessageBox::information(this, "Failure", "The logout failed");
	}
}
void lobby::ontwoPlayersButtonClicked()
{
	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/queueTwoPlayerGame" },
		cpr::Payload{
			{ "username", Player.getFirstName()}
		}
	);

	if (response.status_code == 201)
	{
		QMessageBox::information(this, "queue", "Please wait for more players to connect");

	}

}
