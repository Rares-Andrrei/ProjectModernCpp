#pragma once

#include <QMainWindow>
#include "ui_MapForThreePlayers.h"
#include"Battle.h"
#include "Route.h"

#include <qstring.h>
#include <qmessagebox.h>
#include "PlayerQString.h"
#include <qtimer.h>

class MapForThreePlayers : public QMainWindow
{
	Q_OBJECT

public:
	MapForThreePlayers(QWidget *parent = nullptr);
	~MapForThreePlayers();
	void setNumberOfInterractions(int numberOfInterractions);
	void setPlayer(const std::shared_ptr<PlayerQString>& player);
	void setGameInstance(const std::shared_ptr<Route>& GameInstance);
	QColor getColor(const Color::ColorEnum& color);

protected:
	void showEvent(QShowEvent* event) override;


private:
	Ui::MapForThreePlayersClass ui;
	std::shared_ptr<Route> m_GameInstance;
	std::unique_ptr<QTimer> t_checkFinishState;
	int m_numberOfInterractions;
	bool m_validateMove = true;
	std::shared_ptr<PlayerQString> m_player;
private slots:
	void on_zona1_clicked();
	void on_zona2_clicked();
	void on_zona3_clicked();
	void on_zona4_clicked();
	void on_zona5_clicked();
	void on_zona6_clicked();
	void on_zona7_clicked();
	void on_zona8_clicked();
	void on_zona9_clicked();
	void on_zona10_clicked();
	void on_zona11_clicked();
	void on_zona12_clicked();
	void on_zona13_clicked();
	void on_zona14_clicked();
	void on_zona15_clicked();
	void on_CheckFinishState_Timeout();
};
