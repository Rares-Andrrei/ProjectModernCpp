#pragma once

#include <QMainWindow>
#include "ui_logIn.h"

#include <QString>
#include <QMessageBox>
#include <memory>
#include "Route.h"
#include "lobby.h"



class logIn : public QMainWindow
{
	Q_OBJECT

public:
	logIn(std::shared_ptr<Route> routes, QWidget* parent = nullptr);

private:
	Ui::logInClass ui;
	std::shared_ptr<lobby> lobbyWindow;
	std::shared_ptr<Route> m_routes;
private slots:
	void onEnterButtonClicked();
	void onGoBackButtonClicked();
	void onShowPasswordButtonChecked();
};
