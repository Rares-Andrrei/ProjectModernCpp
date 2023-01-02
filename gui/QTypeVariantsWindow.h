#pragma once

#include <QMainWindow>
#include "ui_QTypeVariantsWindow.h"
#include <string>
#include <QTimer>

class QTypeVariantsWindow : public QMainWindow
{
	Q_OBJECT

public:
	QTypeVariantsWindow(QWidget* parent = nullptr);
	~QTypeVariantsWindow();
	void requestQuestion();

protected:
	void showEvent(QShowEvent* event) override;

private slots:
	void on_Variant1_clicked();
	void on_Variant2_clicked();
	void on_Variant3_clicked();
	void on_Variant4_clicked();
	void on_Variant_clicked();
	void on_Enter_clicked();

	QPushButton* m_Variant = nullptr;
	QString variant = "";
	Ui::QTypeVariantsWindowClass ui;
};
