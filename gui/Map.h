#pragma once

#include <QMainWindow>
#include "ui_Map.h"
#include"Battle.h"
#include "Route.h"

#include <qstring.h>
#include <qmessagebox.h>
#include "PlayerQString.h"
#include <qtimer.h>
#include <qthread.h>
#include "BoardInterpretation.h"
#include "GamePhaseEnum.h"

class Map : public QMainWindow
{
	Q_OBJECT

public:
	Map(QWidget* parent = nullptr);
	~Map();

	void setPlayer(const std::shared_ptr<PlayerQString>& player);
	void setPlayers(const std::vector<std::shared_ptr<PlayerQString>>& players);
	void setGameInstance(const std::shared_ptr<Route>& GameInstance);
	void setBoard(const std::shared_ptr<BoardInterpretation>& board);
	void setPhase(GamePhase gamePhase);
	QColor getColor(const Color::ColorEnum& color);

	void Send_Response_To_Server(int ZoneId);

	void disableAllButtons();
	void enableAllButtons();
	void updateAZone(QAbstractButton* button, const Color::ColorEnum& color);

signals:
	void emitMapUpdatedChooseRegionsPhase();

private:
	Ui::MapClass ui;
	std::shared_ptr<BoardInterpretation> m_board;
	std::shared_ptr<Route> m_GameInstance;
	bool m_isBasePhase;

	GamePhase m_gamePhase : 3 = GamePhase::None;
	std::shared_ptr<PlayerQString> m_player;
	std::vector<std::shared_ptr<PlayerQString>>m_players;
	std::shared_ptr<Battle>BattleWindow;

	void playersAvatar();

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

};
