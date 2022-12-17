#include "logIn.h"
#include <cpr/cpr.h>
#include <crow.h>
#include <string>

logIn::logIn(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	lobbyWindow.reset(new lobby());

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
	usernameString=username.toLocal8Bit().constData();
	passwordString = password.toLocal8Bit().constData();

	if (usernameString.empty() || passwordString.empty())
	{
		QMessageBox::about(this, "Log in error", "Please fill in all the fields");
		return;
	}
	
	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/verifylogininfo" },
		cpr::Payload{
			{ "username", usernameString },
			{ "password", passwordString }
		}
	);

	if (response.status_code == 200 || response.status_code == 202) {
		QMessageBox::information(this, "Success", "Account was found");
		QApplication::closeAllWindows();
		lobbyWindow->show();
	}
	else {
		QMessageBox::information(this, "Failure", "The account was not found");
	}
}
