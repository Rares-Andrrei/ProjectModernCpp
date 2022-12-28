#include "signUp.h"
#include <cpr/cpr.h>
#include "Route.h"
#include "CredentialErrors.h"

signUp::signUp(Route& routes, QWidget* parent)
	: m_routes{ routes }, QMainWindow(parent)
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
	CredentialErrors check = m_routes.signUp(usernameString, passwordString, nicknameString);
	if (check == CredentialErrors::NameSize)
	{
		QMessageBox::about(this, "Name size error", "Your name must containt at least 6 caracters");
		return;
	}
	else if (check == CredentialErrors::UsernameSize)
	{
		QMessageBox::about(this, "Username size error", "Your Username must containt at least 6 caracters");
		return;
	}
	else if (check == CredentialErrors::PasswordSize)
	{
		QMessageBox::about(this, "Passwor size error", "Your Password must containt at least 6 caracters");
		return;
	}
	else if (check == CredentialErrors::UserTaken)
	{
		QMessageBox::about(this, "Username error", "This Username is already taken");
		return;
	}
	else if (check == CredentialErrors::NameTaken)
	{
		QMessageBox::about(this, "Name error", "This name is already taken");
		return;
	}
	else if ((check == CredentialErrors::Valid))
	{
		QMessageBox::about(this, "Success", "Account was registered");
		return;
	}
	else
	{
		QMessageBox::information(this, "Failure", "An unknown error occured");
		return;
	}
}
