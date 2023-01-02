#include "logIn.h"
#include <cpr/cpr.h>
#include <crow.h>
#include "CredentialErrors.h"
#include "Route.h"
#include <string>

logIn::logIn(Route& routes, QWidget* parent)
	: m_routes{ routes }, QMainWindow(parent)
{
	ui.setupUi(this);
	lobbyWindow.reset(new lobby(m_routes));

	ui.l_password->setEchoMode(QLineEdit::Password);

	connect(ui.enterButton, SIGNAL(clicked()), SLOT(onEnterButtonClicked()));
	connect(ui.goBackButton, SIGNAL(clicked()), SLOT(onGoBackButtonClicked()));
	connect(ui.showPasswordButton, SIGNAL(clicked()), SLOT(onShowPasswordButtonChecked()));

	ui.l_username->setPlaceholderText("Username");
	ui.l_password->setPlaceholderText("Password");

	ui.l_username->setClearButtonEnabled(true);
	ui.l_password->setClearButtonEnabled(true);
}

void logIn::onGoBackButtonClicked()
{
	this->close();
}

void logIn::onShowPasswordButtonChecked()
{
	if (ui.showPasswordButton->checkState() == Qt::Checked)
		ui.l_password->setEchoMode(QLineEdit::Normal);
	else
		ui.l_password->setEchoMode(QLineEdit::Password);
}

void logIn::onEnterButtonClicked()
{
	QString username = ui.l_username->text();
	QString password = ui.l_password->text();

	std::string usernameString, passwordString;
	usernameString = username.toLocal8Bit().constData();
	passwordString = password.toLocal8Bit().constData();

	if (usernameString.empty() || passwordString.empty())
	{
		QMessageBox::about(this, "Log in error", "Please fill in all the fields");
		return;
	}
	CredentialErrors check = m_routes.login(usernameString, passwordString);
	switch (check)
	{
	case CredentialErrors::IncorrectAccount:
		QMessageBox::information(this, "Failure", "Account was not found");
		return;
	case CredentialErrors::IncorrectPassword:
		QMessageBox::information(this, "Failure", "Incorrect password");
		return;
	case CredentialErrors::Valid:
		QMessageBox::information(this, "Success", "Account was found");
		QApplication::closeAllWindows();
		lobbyWindow->show();
		break;
	default:
		QMessageBox::information(this, "Failure", "An unknown error has occured");
		break;
	}
}
