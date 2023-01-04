#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui.h"
#include "Route.h"

#include "signUp.h"
#include "logIn.h"

class gui : public QMainWindow
{
    Q_OBJECT

public:
    gui(Route& routes, QWidget* parent = Q_NULLPTR);

private:
    Ui::guiClass ui;

    Route& m_routes;
    std::shared_ptr<signUp> signUpWindow;
    std::shared_ptr<logIn> logInWindow;

private slots:
    void onPlayButtonClicked();
    void onSignUpButtonClicked();
    void onLogInButtonClicked();
};
