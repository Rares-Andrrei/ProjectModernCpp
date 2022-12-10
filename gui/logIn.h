#pragma once

#include <QMainWindow>
#include "ui_logIn.h"

#include <QString>
#include <QMessageBox>

class logIn : public QMainWindow
{
	Q_OBJECT

public:
	logIn(QWidget* parent = nullptr);

private:
	Ui::logInClass ui;

private slots:
	void onEnterButtonClicked();
};
