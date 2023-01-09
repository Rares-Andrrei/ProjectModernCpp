#pragma once

#include <QMainWindow>
#include "ui_QTypeNumericWindow.h"
#include <memory>
#include "PlayerQString.h"
#include "Route.h"


class QTypeNumericWindow : public QMainWindow
{
	Q_OBJECT

public:
	QTypeNumericWindow(QWidget* parent = nullptr);
	~QTypeNumericWindow();

	void requestQuestion();
	void setPlayer(const std::shared_ptr<PlayerQString>& player);
	void setGameInstance(const std::shared_ptr<Route>& GameInstance);


protected:
	void showEvent(QShowEvent* event) override;



signals:
	void sendOrderToParent(const std::vector<std::pair<Color::ColorEnum, int>>& playerOrder);


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
	void on_Delete_pressed();
	void on_Delete_release();
	void on_Timer_Timeout();
	void on_TimeRemaining_Timeout();

private:
	void disableAllButtons();

	std::shared_ptr<Route> m_GameInstance;
	QTimer* m_TimeRemaining;
	QTimer* m_timer;
	std::shared_ptr<PlayerQString> m_player;
	Ui::QTypeNumericWindowClass ui;
};
