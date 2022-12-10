#include "gui.h"

gui::gui(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	signUpWindow.reset(new signUp());
	logInWindow.reset(new logIn());

	connect(ui.playButton, SIGNAL(clicked()), SLOT(onPlayButtonClicked()));
	connect(ui.signUpButton, SIGNAL(clicked()), SLOT(onSignUpButtonClicked()));
	connect(ui.loginButton, SIGNAL(clicked()), SLOT(onLogInButtonClicked()));
}

void gui::onSignUpButtonClicked()
{
	signUpWindow->show();
}

void gui::onLogInButtonClicked()
{
	logInWindow->show();
}

void gui::onPlayButtonClicked()
{
	ui.stackedWidget->setCurrentIndex(1);
}