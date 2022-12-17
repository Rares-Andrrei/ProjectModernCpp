#pragma once

#include <QMainWindow>
#include "ui_logIn.h"

#include <QString>
#include <QMessageBox>

#include "lobby.h"

class logIn : public QMainWindow
{
	Q_OBJECT

public:
	logIn(QWidget* parent = nullptr);

private:
	Ui::logInClass ui;
	std::shared_ptr<lobby> lobbyWindow;

private slots:
	void onEnterButtonClicked();
	void onGoBackButtonClicked();
	void onShowPasswordButtonChecked();
};
