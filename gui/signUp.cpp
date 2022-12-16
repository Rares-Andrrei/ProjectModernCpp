#include "signUp.h"
#include <cpr/cpr.h>

signUp::signUp(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.s_password->setEchoMode(QLineEdit::Password);
	ui.s_confirmPassword->setEchoMode(QLineEdit::Password);

	connect(ui.enterButton, SIGNAL(clicked()), SLOT(onEnterButtonClicked()));
	connect(ui.goBackButton, SIGNAL(clicked()), SLOT(onGoBackButtonClicked()));
	connect(ui.showPasswordButton, SIGNAL(clicked()), SLOT(onShowPasswordButtonChecked()));
	connect(ui.showConfirmedPasswordButton, SIGNAL(clicked()), SLOT(onShowConfirmedPasswordButtonChecked()));

	ui.s_name->setPlaceholderText("Name");
	ui.s_username->setPlaceholderText("Username");
	ui.s_password->setPlaceholderText("Password");
	ui.s_confirmPassword->setPlaceholderText("Confirm password");

	ui.s_name->setClearButtonEnabled(true);
	ui.s_username->setClearButtonEnabled(true);
	ui.s_password->setClearButtonEnabled(true);
	ui.s_confirmPassword->setClearButtonEnabled(true);
}

void signUp::onGoBackButtonClicked()
{
	this->close();
}

void signUp::onShowPasswordButtonChecked()
{
	if (ui.showPasswordButton->checkState()==Qt::Checked)
		ui.s_password->setEchoMode(QLineEdit::Normal);
	else
		ui.s_password->setEchoMode(QLineEdit::Password);
}

void signUp::onShowConfirmedPasswordButtonChecked()
{
	if (ui.showConfirmedPasswordButton->checkState() == Qt::Checked)
		ui.s_confirmPassword->setEchoMode(QLineEdit::Normal);
	else
		ui.s_confirmPassword->setEchoMode(QLineEdit::Password);
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
	{
		QMessageBox::about(this, "Sign up error", "The passwords do not match");
		return;
	}

	std::string usernameString, passwordString, nicknameString;
	usernameString = username.toLocal8Bit().constData();
	passwordString = password.toLocal8Bit().constData();
	nicknameString = name.toLocal8Bit().constData();
	if (usernameString.empty() || passwordString.empty() || nicknameString.empty())
	{
		QMessageBox::about(this, "Sign up error", "Please fill in all the fields");
		return;
	}
	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/validateusername" },
		cpr::Payload{
			{"username", usernameString}
		}
	);
	if (response.status_code == 400)
	{
		QMessageBox::information(this, "Username already used", "Selected Username isn't available");
		return;
	}
	response = cpr::Put(
		cpr::Url{ "http://localhost:18080/register" },
		cpr::Payload{
			{ "username", usernameString },
			{ "password", passwordString },
			{ "nickname", nicknameString }
		}
	);

	if (response.status_code == 200) // register succesful
	{
		QMessageBox::information(this, "Success", "Account was registered");
	}
	else {
		QMessageBox::information(this, "Failure", "The account wasn't registered");
	}
}
