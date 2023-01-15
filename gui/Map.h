#pragma once

#include <QMainWindow>
#include "ui_Map.h"
#include "Route.h"
#include <qstring.h>
#include <qmessagebox.h>
#include "PlayerQString.h"
#include <qtimer.h>
#include <qthread.h>
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
	void emitGetNextDuel();

public slots:
	void onButtonClickedSignal(int index);

private:
	Ui::MapClass ui;
	
	std::shared_ptr<Route> m_GameInstance;
	GamePhase m_gamePhase : 3 = GamePhase::None;

	std::shared_ptr<QVBoxLayout> layout;
	std::shared_ptr<GridButtons> m_gridButtons;
	std::shared_ptr<PlayerQString> m_player;
	std::vector<std::shared_ptr<PlayerQString>>m_players;

	void playersAvatar();
	void setupGridButtons();
};