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
#include "GridButtons.h"
#include <qrandom.h>

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
	void send_Attacker_Response_To_Server(int ZoneId);
	void getUpdatedZones(const std::vector<std::tuple<int, Color::ColorEnum, int, int>>& UpdatedZones);
	void getUpdatedZones(const std::vector<std::tuple<int, Color::ColorEnum, int>>& UpdatedZones);


	void disableAllButtons();
	void enableAllButtons();

	void updatePlayersInfo();

signals:
	void emitMapUpdatedChooseRegionsPhase();
	void emitDuelParticipants(const std::pair<Color::ColorEnum, Color::ColorEnum>& duelParticipants);

public slots:
	void onButtonClickedSignal(int index);

private:
	//int currentButtonIndex;
	Ui::MapClass ui;
	std::shared_ptr<BoardInterpretation> m_board;
	std::shared_ptr<Route> m_GameInstance;

	GamePhase m_gamePhase : 3 = GamePhase::None;

	std::shared_ptr<QVBoxLayout> layout;
	GridButtons* m_gridButtons;

	std::shared_ptr<PlayerQString> m_player;
	std::vector<std::shared_ptr<PlayerQString>>m_players;
	std::shared_ptr<Battle>BattleWindow;

	void playersAvatar();
	//void ButtonClicked(int ZoneId);
	void setupGridButtons();

};
