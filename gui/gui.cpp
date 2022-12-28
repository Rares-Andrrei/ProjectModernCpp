#include "gui.h"

gui::gui(Route& routes, QWidget* parent)
	: m_routes{ routes }, QMainWindow(parent)
{
	ui.setupUi(this);

	signUpWindow.reset(new signUp(m_routes));
	logInWindow.reset(new logIn(m_routes));

	connect(ui.playButton, SIGNAL(clicked()), SLOT(onPlayButtonClicked()));
	connect(ui.signUpButton, SIGNAL(clicked()), SLOT(onSignUpButtonClicked()));
	connect(ui.loginButton, SIGNAL(clicked()), SLOT(onLogInButtonClicked()));

	ui.loginButton->setToolTip("Log in with an existing account");
	ui.signUpButton->setToolTip("Create a new account");
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