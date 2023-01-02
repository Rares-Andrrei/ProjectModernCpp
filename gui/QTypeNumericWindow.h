#pragma once

#include <QMainWindow>
#include "ui_QTypeNumericWindow.h"

class QTypeNumericWindow : public QMainWindow
{
	Q_OBJECT

public:
	QTypeNumericWindow(QWidget *parent = nullptr);
	~QTypeNumericWindow();

	void requestQuestion();

private slots:
	void on_Number0_clicked();
	void on_Number1_clicked();
	void on_Number2_clicked();
	void on_Number3_clicked();
	void on_Number4_clicked();
	void on_Number5_clicked();
	void on_Number6_clicked();
	void on_Number7_clicked();
	void on_Number8_clicked();
	void on_Number9_clicked();
	void on_Enter_clicked();

	void on_Delete_clicked();
	//void on_Delete_pressed();
	//void on_Delete_release();
	//void on_Timer_Timeout();

private:
	//QTimer* m_timer;
	Ui::QTypeNumericWindowClass ui;
};
