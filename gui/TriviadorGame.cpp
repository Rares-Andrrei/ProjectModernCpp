#include "TriviadorGame.h"

TriviadorGame::TriviadorGame(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	/*MapWindow.reset(new Map(this));*/
	MapWindow.reset(new Map(this));

	m_QTypeNumericWindow = std::make_unique<QTypeNumericWindow>(this);
	connect(m_QTypeNumericWindow.get(), &QTypeNumericWindow::sendOrderToParent, this, &TriviadorGame::onSendOrderToParent);

	m_QTypeVariantsWindow = std::make_unique<QTypeVariantsWindow>(this);

	t_NumericWindowTimer = std::make_unique<QTimer>();
	t_NumericWindowTimer->setInterval(500);
	connect(t_NumericWindowTimer.get(), &QTimer::timeout, this, &TriviadorGame::checkNumericWindowClosed);

	t_checkCurrentPhase = std::make_unique<QTimer>();
	t_checkCurrentPhase->setInterval(500);
	connect(t_checkCurrentPhase.get(), &QTimer::timeout, this, &TriviadorGame::checkCurrentPhase);

	connect(MapWindow.get(), &Map::emitMapUpdatedChooseRegionsPhase, this, &TriviadorGame::updateTheQueueStatus);
	connect(MapWindow.get(), &Map::emitDuelParticipants, this, &TriviadorGame::duelParticipants);

	connect(MapWindow.get(), &Map::emitGetNextDuel, this, &TriviadorGame::startNextDuel);

	connect(m_QTypeVariantsWindow.get(), &QTypeVariantsWindow::emitDuelStatus, this, &TriviadorGame::getDuelStatus);
	connect(m_QTypeNumericWindow.get(), &QTypeNumericWindow::emitTieBreakerDuelStatus, this, &TriviadorGame::getTieBreakerDuelStatus);
}

TriviadorGame::~TriviadorGame()
{}

void TriviadorGame::setNumberOfPlayers(const uint16_t& numberOfPlayers)
{
	m_numberOfPlayers = numberOfPlayers;
	if (m_numberOfPlayers <= 2)
	{
		m_numberOfInteractionsLeft = 2;
	}
	else {
		m_numberOfInteractionsLeft = numberOfPlayers - 1;
	}
}

void TriviadorGame::setPlayer(const std::shared_ptr<PlayerQString>& player)
{
	m_player = player;
	MapWindow->setPlayer(m_player);
	m_QTypeNumericWindow->setPlayer(m_player);
	m_QTypeVariantsWindow->setPlayer(m_player);
}

void TriviadorGame::setPlayers(const std::vector<std::shared_ptr<PlayerQString>>& players)
{
	m_players = players;
	MapWindow->setPlayers(players);
}

void TriviadorGame::setGameInstance(const std::shared_ptr<Route>& GameInstance)
{
	m_GameInstance = GameInstance;
	MapWindow->setGameInstance(m_GameInstance);
	m_QTypeNumericWindow->setGameInstance(m_GameInstance);
	m_QTypeVariantsWindow->setGameInstance(m_GameInstance);
}

void TriviadorGame::showEvent(QShowEvent* event)
{
	t_checkCurrentPhase->start();
	this->close();
}

void TriviadorGame::chooseBasePhase()
{
	t_NumericWindowTimer->start();
	changePhase = false;
	m_gamePhase = GamePhase::ChooseBase;

	m_QTypeNumericWindow->requestQuestion();
	m_QTypeNumericWindow->enableAllButtons();
	m_QTypeNumericWindow->show();
}

void TriviadorGame::chooseRegionsPhase()
{
	changePhase = false;
	m_gamePhase = GamePhase::ChooseRegions;

	QThread::msleep(1000);
	m_QTypeNumericWindow->requestQuestion();
	m_QTypeNumericWindow->enableAllButtons();
	m_QTypeNumericWindow->show();
}

void TriviadorGame::duelsPhase()
{
	QThread::msleep(QRandomGenerator::global()->bounded(1, 50));
	auto color = m_GameInstance->getAttackerColor();
	qDebug("Attacker color : %d", Color::ColorToInt(color));
	QThread::msleep(QRandomGenerator::global()->bounded(1, 50));
	MapWindow->hide();

	if (color == Color::ColorEnum::None)
	{
		m_gamePhase = GamePhase::End;
		qDebug("End game");
		EndGame();
		return;
	}
	QThread::msleep(QRandomGenerator::global()->bounded(1, 50));
	if (m_player->getColor() == color)
	{
		qDebug("current player is the Attacker ");
		MapWindow->enableAllButtons();
		QThread::msleep(QRandomGenerator::global()->bounded(1, 50));
		MapWindow->show();
	}
	else {
		qDebug("current player is inactive ");
		MapWindow->disableAllButtons();
		MapWindow->send_Attacker_Response_To_Server(-1);
	}
}

void TriviadorGame::EndGame()
{
	changePhase = false;

	t_checkCurrentPhase->stop();
	t_NumericWindowTimer->stop();

	m_gamePhase = GamePhase::End;
	// Request :: de primit rezultatele finale
	displayPodium();

	// Request :: terminare joc si aducerea jucatori in lobby
	// GUI :: revenire la pagina de lobby
	this->close();
	this->parentWidget()->show();
}

void TriviadorGame::displayPodium()
{
	// Request :: de primit podiumul ( jucatori si scoruri  )
	// GUI :: deschidere fereastra cu podiumul
	// GUI :: fereastra primeste un vector de jucatori si scoruri pe care ii va afisa 
	// GUI :: inchidere fereastra cu podiumul
}

void TriviadorGame::checkNumericWindowClosed()
{
	if (changePhase == true) // daca o faza s-a terminat , asteptam sa trecem la urmatoarea
	{
		return;
	}

	if (m_gamePhase == GamePhase::ChooseBase)
	{
		if (!MapWindow->isVisible() && !m_QTypeNumericWindow->isVisible())
		{
			nextPlayerInQueue();
		}
	}
	else if (m_gamePhase == GamePhase::ChooseRegions)
	{
		if (!MapWindow->isVisible() && !m_QTypeNumericWindow->isVisible())
		{
			if (!m_playerOrder.empty())
			{
				nextPlayerInQueue();
			}
			else
			{
				chooseRegionsPhase();
			}
		}
	}
}


void TriviadorGame::checkCurrentPhase()
{
	if (checkIfWindowsAreClosed() == false)
	{
		return;
	}

	if (m_gamePhase == GamePhase::None && changePhase == true)
	{
		MapWindow->setPhase(GamePhase::ChooseBase);
		chooseBasePhase();
	}
	else if (m_gamePhase == GamePhase::ChooseBase && changePhase == true)
	{
		MapWindow->setPhase(GamePhase::ChooseRegions);
		chooseRegionsPhase();
	}
	else if (m_gamePhase == GamePhase::ChooseRegions && changePhase == true)
	{
		changePhase = false;
		m_gamePhase = GamePhase::Duels;
		MapWindow->setPhase(GamePhase::Duels);
		duelsPhase();
	}
	else if (m_gamePhase == GamePhase::Duels && changePhase == true)
	{
		MapWindow->setPhase(GamePhase::End);
		EndGame();
	}
}

bool TriviadorGame::checkIfWindowsAreClosed()
{
	for (auto& window : findChildren<QWidget*>())
	{
		if (window->isVisible())
		{
			return false;
		}
	}
	return true;
}

void TriviadorGame::nextPlayerInQueue()
{
	QThread::msleep(QRandomGenerator::global()->bounded(1, 50));
	if (changePhase == true)
	{
		return;
	}
	if (m_playerOrder.empty() && m_gamePhase == GamePhase::ChooseBase)
	{
		changePhase = true;
		return;
	}
	if (!MapWindow->isVisible())
	{
		// daca jucatorul curent nu e cel activ,  atunci doar va vedea harta
		if (m_player->getColor() != m_playerOrder.front().first)
		{
			MapWindow->disableAllButtons();
			MapWindow->Send_Response_To_Server(-1); // si va trimite catre server o zona invalida , ca sa stie cum sa identifice zona schibmata 
		}
		else
		{
			MapWindow->enableAllButtons();
			QThread::msleep(QRandomGenerator::global()->bounded(1, 50));
			MapWindow->show();
		}
	}
}

void TriviadorGame::updateTheQueueStatus()
{
	if (changePhase == true)
	{
		return;
	}
	if (m_GameInstance->checkIfBoardIsFull() == true && m_gamePhase == GamePhase::ChooseRegions)
	{
		m_gamePhase = GamePhase::Duels;
		t_checkCurrentPhase->stop();
		t_NumericWindowTimer->stop();
		m_QTypeNumericWindow->setDuelPhase();
		MapWindow->setPhase(GamePhase::Duels);

		while (!m_playerOrder.empty())
		{
			m_playerOrder.pop();
		}
		MapWindow->close();
		duelsPhase();
		return;
	}
	if (m_gamePhase == GamePhase::Duels)
	{
		duelsPhase();
		return;
	}

	if (m_gamePhase == GamePhase::ChooseBase)
	{
		m_playerOrder.pop();
		return;
	}
	m_numberOfInteractionsLeft--;
	if (m_numberOfInteractionsLeft == 0)
	{
		m_playerOrder.pop();
		if (m_gamePhase == GamePhase::ChooseRegions)
		{
			if (m_playerOrder.empty())
			{
				m_numberOfInteractionsLeft = m_players.size();
				if (m_numberOfPlayers != 2)
				{
					m_numberOfInteractionsLeft--;
				}
				return;
			}
			if (m_numberOfPlayers == 2)
			{
				m_numberOfInteractionsLeft = m_playerOrder.size();
			}
			else
			{
				m_numberOfInteractionsLeft = m_playerOrder.size() - 1;
			}
		}
	}
}

void TriviadorGame::startNextDuel()
{
	qDebug("called duel function");
	duelsPhase();
}

void TriviadorGame::getUpdatedZonesAfterWin(const std::vector<std::tuple<int, Color::ColorEnum, int>>& updatedZones)
{
	MapWindow->getUpdatedZones(updatedZones);
	QThread::msleep(QRandomGenerator::global()->bounded(1, 50));
	MapWindow->updatePlayersInfo();
}

void TriviadorGame::duelParticipants(const std::pair<Color::ColorEnum, Color::ColorEnum>& duelParticipants)
{
	qDebug("called duel participants , they are %d and %d", Color::ColorToInt(duelParticipants.first), Color::ColorToInt(duelParticipants.second));
	QThread::msleep(QRandomGenerator::global()->bounded(1, 50));
	m_QTypeVariantsWindow->requestQuestion();
	QThread::msleep(QRandomGenerator::global()->bounded(1, 50));
	if (m_player->getColor() == duelParticipants.first || m_player->getColor() == duelParticipants.second)
	{
		qDebug("showing Variants Window for player %d", Color::ColorToInt(m_player->getColor()));
		QThread::msleep(QRandomGenerator::global()->bounded(1, 50));
		m_QTypeVariantsWindow->enableAllButtons();
		m_QTypeVariantsWindow->showWindow();
	}
	else
	{
		qDebug("showing duel window for INCATIVE player %d", Color::ColorToInt(m_player->getColor()));
		m_QTypeVariantsWindow->disableAllButtons();
		m_QTypeVariantsWindow->sendResponseToServer(-1, Color::ColorEnum::None);
	}
}

void TriviadorGame::tieBreakerRound(const std::pair<Color::ColorEnum, Color::ColorEnum>& duelParticipants)
{
	QThread::msleep(QRandomGenerator::global()->bounded(1, 50));
	m_QTypeNumericWindow->requestQuestion();
	QThread::msleep(QRandomGenerator::global()->bounded(1, 50));
	if (m_player->getColor() == duelParticipants.first || m_player->getColor() == duelParticipants.second)
	{
		m_QTypeNumericWindow->enableAllButtons();
		m_QTypeNumericWindow->show();
	}
	else
	{
		m_QTypeNumericWindow->disableAllButtons();
		m_QTypeNumericWindow->sendResponseToServerAndGetDuelStatus(INT_MAX, INT_MAX, Color::ColorEnum::None);
	}
}

void TriviadorGame::getTieBreakerResults(const std::vector<std::tuple<int, Color::ColorEnum, int, int>>& UpdatedZones, const std::vector<std::pair<int, Color::ColorEnum>>& updatedPlayers)
{
	MapWindow->getUpdatedZones(UpdatedZones);
}

void TriviadorGame::onSendOrderToParent(const std::queue<std::pair<Color::ColorEnum, int>>& playerOrder)
{
	m_playerOrder = playerOrder;
	m_QTypeNumericWindow->close();
}

void TriviadorGame::getDuelStatus(DuelManager& duelStatus)
{
	m_QTypeVariantsWindow->close();
	if (duelStatus.getDuelStatus() == DuelManager::duelStatus::Lose)
	{
		qDebug("Duel was lost , now a new duel should start");
		startNextDuel();
	}
	else if (duelStatus.getDuelStatus() == DuelManager::duelStatus::lifeTaken)
	{
		auto attackInfo = duelStatus.getUpdatedBase();
		auto& [zone, life, score, zoneColor, attacker, defender] = attackInfo;
		std::vector<std::tuple<int, Color::ColorEnum, int, int>> updatedZones;
		qDebug("Life was taken , now a new duel should start , with same people %d %d", Color::ColorToInt(attacker), Color::ColorToInt(defender));
		updatedZones.push_back(std::make_tuple(zone, zoneColor, score, life));
		MapWindow->getUpdatedZones(updatedZones);

		duelParticipants({ std::get<4>(attackInfo), std::get<5>(attackInfo) });
	}
	else if (duelStatus.getDuelStatus() == DuelManager::duelStatus::Win)
	{
		auto updatedZones = duelStatus.getUpdatedZones();
		qDebug("Duel was won , now a new duel should start , and change the zones %d", Color::ColorToInt(std::get<1>(updatedZones[0])));
		getUpdatedZonesAfterWin(updatedZones);
	}
	else if (duelStatus.getDuelStatus() == DuelManager::duelStatus::Draw)
	{
		auto tieBreakterParticipants = duelStatus.getTieBreakerParticipants();
		qDebug("Duel was draw , now a new duel should start between %d and %d", Color::ColorToInt(tieBreakterParticipants.first), Color::ColorToInt(tieBreakterParticipants.second));
		tieBreakerRound(tieBreakterParticipants);
	}
}

void TriviadorGame::getTieBreakerDuelStatus(DuelManager& duelStatus)
{
	m_QTypeNumericWindow->close();
	if (duelStatus.getDuelStatus() == DuelManager::duelStatus::Lose)
	{
		qDebug("Duel was lost , now a new duel should start");
		startNextDuel();
	}
	else if (duelStatus.getDuelStatus() == DuelManager::duelStatus::lifeTaken)
	{
		auto attackInfo = duelStatus.getUpdatedBase();
		auto& [zone, score, life, zoneColor, attacker, defender] = attackInfo;
		qDebug("Life was taken , now a new duel should start , with same people %d %d", Color::ColorToInt(attacker), Color::ColorToInt(defender));

		std::vector<std::tuple<int, Color::ColorEnum, int, int>> updatedZones;
		updatedZones.push_back(std::make_tuple(zone, zoneColor, score, life));
		MapWindow->getUpdatedZones(updatedZones);
		QThread::msleep(QRandomGenerator::global()->bounded(1, 50));
		MapWindow->updatePlayersInfo();

		duelParticipants({ std::get<4>(attackInfo), std::get<5>(attackInfo) });
	}
	else if (duelStatus.getDuelStatus() == DuelManager::duelStatus::Win)
	{

		auto updatedZones = duelStatus.getUpdatedZones();
		qDebug("Duel was won , now a new duel should start , and change the zones %d", Color::ColorToInt(std::get<1>(updatedZones[0])));
		getUpdatedZonesAfterWin(updatedZones);
	}
}