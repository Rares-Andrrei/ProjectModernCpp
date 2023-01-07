#pragma once

#include <QMainWindow>
#include "ui_Map.h"
#include"Battle.h"

#include <qstring.h>
#include <qmessagebox.h>
#include "PlayerQString.h"
#include <qtimer.h>

class Map : public QMainWindow
{
	Q_OBJECT

public:
	Map(QWidget* parent = nullptr);
	~Map();

	void setNumberOfInterractions(int numberOfInterractions);
	void setPlayer(const std::shared_ptr<PlayerQString>& player);
	QColor getColor(const Color::ColorEnum& color);

protected:
	void showEvent(QShowEvent* event) override;

private:
	Ui::MapClass ui;

	std::unique_ptr<QTimer> t_checkFinishState;
	int m_numberOfInterractions;
	bool m_validateMove = true;
	std::shared_ptr<PlayerQString> m_player;
	std::shared_ptr<Battle>BattleWindow;

private slots:
	void onzona1Clicked();
	void onzona2Clicked();
	void onzona3Clicked();
	void onzona4Clicked();
	void onzona5Clicked();
	void onzona6Clicked();
	void onzona7Clicked();
	void onzona8Clicked();
	void onzona9Clicked();

	void on_CheckFinishState_Timeout();
};
