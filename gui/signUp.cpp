#include "signUp.h"
#include <cpr/cpr.h>

signUp::signUp(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.enterButton, SIGNAL(clicked()), SLOT(onEnterButtonClicked()));
}

void signUp::onEnterButtonClicked()
{
    QString name = ui.s_name->text();
    QString username = ui.s_username->text();
    QString password = ui.s_password->text();
    QString confirmPassword = ui.s_confirmPassword->text();

    //daca username ul nu e unic, eroare
    //daca parola nu e la fel ca confimPassword, eroare

    if (password != confirmPassword)
        QMessageBox::about(this, "Sign up error", "The passwords do not match");
    //else
    //    QMessageBox::about(this, "Sign up", "The account is created successfully, now you can log in");
	std::string usernameString, passwordString, nicknameString;
	usernameString = username.toLocal8Bit().constData();
	passwordString = password.toLocal8Bit().constData();
	nicknameString = name.toLocal8Bit().constData();

	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/register" },
		cpr::Payload{
			{ "username", usernameString },
			{ "password", passwordString },
			{ "nickname", nicknameString }
		}
	);

	if (response.status_code == 200 ) {// register succesful
		QMessageBox::information(this, "Success", "Account was registered");
	}
	else {
		QMessageBox::information(this, "Failure", "The account wasn't registered");
	}
}
