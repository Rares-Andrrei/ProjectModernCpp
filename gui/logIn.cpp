#include "logIn.h"
#include <cpr/cpr.h>
#include <crow.h>
#include <string>

logIn::logIn(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.enterButton, SIGNAL(clicked()), SLOT(onEnterButtonClicked()));
}

void logIn::onEnterButtonClicked()
{
    QString username = ui.l_username->text();
    QString password = ui.l_password->text();

	std::string usernameString, passwordString;
	usernameString=username.toLocal8Bit().constData();
	passwordString = password.toLocal8Bit().constData();
	
	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/verifylogininfo" },
		cpr::Payload{
			{ "username", usernameString },
			{ "password", passwordString }
		}
	);

	if (response.status_code == 200 || response.status_code == 202) {
		QMessageBox::information(this, "Success", "Account was found");
	}
	else {
		QMessageBox::information(this, "Failure", "The account was not found");
	}
}
