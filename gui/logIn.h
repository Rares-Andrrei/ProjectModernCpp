#pragma once

#include <QMainWindow>
#include "ui_logIn.h"

#include <QString>
#include <QMessageBox>
#include "Route.h"
#include "lobby.h"



class logIn : public QMainWindow
{
	Q_OBJECT

public:
	logIn(Route& routes, QWidget* parent = nullptr);

private:
	Ui::logInClass ui;
	std::shared_ptr<lobby> lobbyWindow;
	Route& m_routes;
private slots:
	void onEnterButtonClicked();
	void onGoBackButtonClicked();
	void onShowPasswordButtonChecked();
};
