#pragma once

#include <QMainWindow>
#include "ui_QTypeNumericWindow.h"
#include <memory>
#include "PlayerQString.h"
#include "Route.h"
#include "GamePhaseEnum.h"

class QTypeNumericWindow : public QMainWindow
{
	Q_OBJECT

public:
	QTypeNumericWindow(QWidget* parent = nullptr);
	~QTypeNumericWindow();

	void requestQuestion();
	void setPlayer(const std::shared_ptr<PlayerQString>& player);
	void setGameInstance(const std::shared_ptr<Route>& GameInstance);
	void setDuelPhase();

	void sendResponseToServerAndGetDuelStatus(int response, int time, const Color::ColorEnum& color);

	void disableAllButtons();
	void enableAllButtons();
	void resetTheWindow();

	void showWindow();
protected:
	void showEvent(QShowEvent* event) override;

signals:
	void emitTieBreakerDuelStatus(DuelManager& duelStatus);
	void sendOrderToParent(const std::queue<std::pair<Color::ColorEnum, int>>& playerOrder);

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

	GamePhase m_gamePhase = GamePhase::None;
	std::shared_ptr<Route> m_GameInstance;
	std::unique_ptr<QTimer> m_TimeRemaining;
	std::unique_ptr<QTimer> m_timer;
	std::shared_ptr<PlayerQString> m_player;
	Ui::QTypeNumericWindowClass ui;
};
