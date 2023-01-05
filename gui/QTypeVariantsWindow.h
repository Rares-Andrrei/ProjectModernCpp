#pragma once

#include <QMainWindow>
#include "ui_QTypeVariantsWindow.h"
#include "PlayerQString.h"
#include <string>
#include <QTimer>
#include <memory>

class QTypeVariantsWindow : public QMainWindow
{
	Q_OBJECT

public:
	QTypeVariantsWindow(QWidget* parent = nullptr);
	~QTypeVariantsWindow();
	void requestQuestion();
	void setPlayer(const std::shared_ptr<PlayerQString>& player);
protected:
	void showEvent(QShowEvent* event) override;

private slots:
	void on_Variant1_clicked();
	void on_Variant2_clicked();
	void on_Variant3_clicked();
	void on_Variant4_clicked();
	void on_Variant_clicked();
	void on_Enter_clicked();
	void on_TimeRemaining_Timeout();

	void onFiftyFiftyButtonClicked();

private:
	void buttonsConnections();
	void createTimeSlider();
	void createAnswerVariants();
	void advantageButtonEnabled();

	void disableAllButtons();
	
	QPushButton* m_Variant = nullptr;
	QTimer* m_timeRemaining;
	QString variant = "";
	std::shared_ptr<PlayerQString> m_player;
	Ui::QTypeVariantsWindowClass ui;
};
