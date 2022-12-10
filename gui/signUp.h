#pragma once

#include <QMainWindow>
#include "ui_signUp.h"

#include <QString>
#include <QMessageBox>

class signUp : public QMainWindow
{
	Q_OBJECT

public:
	signUp(QWidget* parent = nullptr);

private:
	Ui::signUpClass ui;

private slots:
	void onEnterButtonClicked();
};
