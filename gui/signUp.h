#pragma once

#include <QMainWindow>
#include "ui_signUp.h"

#include "Route.h"
#include <QString>
#include <QMessageBox>

class signUp : public QMainWindow
{
	Q_OBJECT

public:
	signUp(std::shared_ptr<Route> routes, QWidget* parent = nullptr);

private:
	Ui::signUpClass ui;
	std::shared_ptr<Route> m_routes;
private slots:
	void onEnterButtonClicked();
	void onGoBackButtonClicked();
	void onShowPasswordButtonChecked();
	void onShowConfirmedPasswordButtonChecked();

};
