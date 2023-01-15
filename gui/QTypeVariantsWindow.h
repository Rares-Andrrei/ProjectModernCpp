#pragma once

#include <QMainWindow>
#include "ui_QTypeVariantsWindow.h"
#include "PlayerQString.h"
#include "Route.h"
#include <string>
#include <QTimer>
#include <memory>
#include <qstring.h>

class QTypeVariantsWindow : public QMainWindow
{
	Q_OBJECT

public:
	QTypeVariantsWindow(QWidget* parent = nullptr);
	~QTypeVariantsWindow();
	void requestQuestion();
	void setPlayer(const std::shared_ptr<PlayerQString>& player);
	void setGameInstance(const std::shared_ptr<Route>& GameInstance);

	void sendResponseToServer(const QString& response);

	void disableAllButtons();
	void enableAllButtons();

signals:
	void emitTieBreakerParticipants(const std::pair<Color::ColorEnum, Color::ColorEnum>& duelParticipants);

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
	void resetTheWindow();


	std::shared_ptr<Route> m_GameInstance;
	QPushButton* m_Variant = nullptr;
	QTimer* m_timeRemaining;
	QString variant = "";
	std::shared_ptr<PlayerQString> m_player;
	Ui::QTypeVariantsWindowClass ui;
};
