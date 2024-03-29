#include "gui.h"

gui::gui(QWidget* parent)
	: QMainWindow(parent)
{
	m_routes = std::make_shared<Route>();

	ui.setupUi(this);

	connect(ui.playButton, SIGNAL(clicked()), SLOT(onPlayButtonClicked()));
	connect(ui.signUpButton, SIGNAL(clicked()), SLOT(onSignUpButtonClicked()));
	connect(ui.loginButton, SIGNAL(clicked()), SLOT(onLogInButtonClicked()));

	ui.loginButton->setToolTip("Log in with an existing account");
	ui.signUpButton->setToolTip("Create a new account");
}

void gui::onSignUpButtonClicked()
{
	signUpWindow.reset(new signUp(m_routes));
	signUpWindow->show();
}

void gui::onLogInButtonClicked()
{
	logInWindow.reset(new logIn(m_routes));
	logInWindow->show();
}

void gui::onPlayButtonClicked()
{
	ui.stackedWidget->setCurrentIndex(1);
}