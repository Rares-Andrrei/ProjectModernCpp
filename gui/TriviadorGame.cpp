#include "TriviadorGame.h"

TriviadorGame::TriviadorGame(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	MapWindow.reset(new Map(this));

	t_NumericWindowTimer = std::make_unique<QTimer>();
	t_NumericWindowTimer->setInterval(500);
	connect(t_NumericWindowTimer.get(), &QTimer::timeout, this, &TriviadorGame::checkNumericWindowClosed);

	t_checkCurrentPhase = std::make_unique<QTimer>();
	t_checkCurrentPhase->setInterval(500);
	connect(t_checkCurrentPhase.get(), &QTimer::timeout, this, &TriviadorGame::checkCurrentPhase);

	t_MapWindowTimer = std::make_unique<QTimer>();
	t_MapWindowTimer->setInterval(500);
	connect(t_MapWindowTimer.get(), &QTimer::timeout, this, &TriviadorGame::checkMapWindowClosed);

	t_VariantsWindowTimer = std::make_unique<QTimer>();
	t_VariantsWindowTimer->setInterval(500);
	connect(t_VariantsWindowTimer.get(), &QTimer::timeout, this, &TriviadorGame::checkVariantsWindowClosed);
}

TriviadorGame::~TriviadorGame()
{}

void TriviadorGame::setNumberOfPlayers(const uint16_t& numberOfPlayers)
{
	m_numberOfPlayers = numberOfPlayers;
	if (m_numberOfPlayers <= 2)
		m_MaxNumberOfDuels = 4 * m_numberOfPlayers;
	else m_MaxNumberOfDuels = 5 * m_numberOfPlayers;

}

void TriviadorGame::displayLoadingMessage(/*const QTimer& timer*/)
{
	// afisare loading screen , parametrizat
}

void TriviadorGame::StartGame()
{
	t_checkCurrentPhase->start();
	t_NumericWindowTimer->start();
	//TODO :
	// afisare loading screen
	// Etape :
	//		alegere baza
	// 		alegere regiuni
	//		dueluri
	// 
	// Endgame
	// afisare loagind screen
	// afisare rezultate
	// 
	// Aducerea jucatorilor inaloi la lobby
	// afisare loading screen

	displayLoadingMessage(/*timer*/); // de discutat timpul de incarcare necesar
	chooseBasePhase();

	//displayLoadingMessage(/*timer*/); // de discutat timpul de incarcare necesar
	//chooseRegionsPhase();

	//displayLoadingMessage(/*timer*/); // de discutat timpul de incarcare necesar
	//duelsPhase();

	//displayLoadingMessage(/*timer*/); // de discutat timpul de incarcare necesar
	//EndGame();
}

void TriviadorGame::setPlayer(const std::shared_ptr<PlayerQString>& player)
{
	m_player = player;
	MapWindow->setPlayer(m_player);
}

void TriviadorGame::setPlayers(const std::vector<std::shared_ptr<PlayerQString>>& players)
{
	m_players = players;
}

void TriviadorGame::showEvent(QShowEvent* event)
{
	t_checkCurrentPhase->start();
	this->hide();
}

void TriviadorGame::chooseBasePhase()
{
	t_NumericWindowTimer->start();
	changePhase = false;
	m_gamePhase = GamePhase::ChooseBase;

	m_QTypeNumericWindow.reset(new QTypeNumericWindow(this));
	m_QTypeNumericWindow->setPlayer(m_player);
	m_QTypeNumericWindow->show();
}

void TriviadorGame::chooseRegionsPhase()
{
	t_MapWindowTimer->start();
	changePhase = false;
	m_gamePhase = GamePhase::ChooseRegions;

	m_QTypeNumericWindow.reset(new QTypeNumericWindow(this));
	m_QTypeNumericWindow->setPlayer(m_player);
	m_QTypeNumericWindow->show();
}

void TriviadorGame::duelsPhase()
{
	m_MapWindowClosed = false;
	changePhase = false;
	t_VariantsWindowTimer->start();

	m_gamePhase = GamePhase::Duels;
	duelFinished = true;
	startDuel();
}

void TriviadorGame::startDuel()
{
	if (m_gamePhase == GamePhase::Duels && m_numberOfDuels < m_MaxNumberOfDuels && duelFinished == true)
	{
		m_duelStatus = DuelStatus::None;
		m_numberOfDuels++;
		duelFinished = false;
		m_MapWindowClosed = false;
		MapWindow->setNumberOfInterractions(1);
		MapWindow->show(); // de schibmat cu o functie prin care se alege o singura zona 
	}
	if (m_numberOfDuels >= m_MaxNumberOfDuels)
	{
		changePhase = true;
	}
}

void TriviadorGame::EndGame()
{
	changePhase = false;

	t_checkCurrentPhase->stop();
	t_MapWindowTimer->stop();
	t_VariantsWindowTimer->stop();
	t_NumericWindowTimer->stop();

	m_gamePhase = GamePhase::End;
	// Request :: de primit rezultatele finale
	displayPodium();

	// Request :: terminare joc si aducerea jucatori in lobby
	// GUI :: revenire la pagina de lobby
	this->close();
	this->parentWidget()->show();
	displayLoadingMessage(/*timer*/); // de discutat timpul de incarcare necesar
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
	if (changePhase == true || serverAproveStatus == false) // daca o faza s-a terminat , asteptam sa trecem la urmatoarea
	{
		return;
	}

	if (m_gamePhase == GamePhase::ChooseBase)
	{
		if (!MapWindow->isVisible() && !m_QTypeNumericWindow->isVisible())
		{
			m_QTypeNumericWindow.reset(new QTypeNumericWindow(this));
			MapWindow->setNumberOfInterractions(m_numberOfPlayers);
			MapWindow->show();
			changePhase = true;
		}
	}
	else if (m_gamePhase == GamePhase::ChooseRegions)
	{
		if (m_MapWindowClosed == false && !MapWindow->isVisible() && !m_QTypeNumericWindow->isVisible())
		{
			m_QTypeNumericWindow.reset(new QTypeNumericWindow(this));
			m_QTypeNumericWindow->setPlayer(m_player);
			MapWindow->setNumberOfInterractions(m_numberOfPlayers * 3 + 1);
			MapWindow->show();
			m_MapWindowClosed = true;
		}
	}
	else if (m_gamePhase == GamePhase::Duels && m_duelStatus == DuelStatus::Draw)
	{
		if (!m_QTypeNumericWindow->isVisible())
		{
			m_duelStatus = DuelStatus::Lose; // statusul va fi primit de la server prin json sau prin response.status_code , poate fi doar WIN sau LOSE , DRAW = LOSE
			if (m_duelStatus == DuelStatus::Win)
			{
				// Request :: de modificat statusul la board  ??
				// GUI :: deschidere fereastra cu harta pentru a se vedea cum zona a fost castigata , in cazul in care sunt indeplinite conditiile
				MapWindow->show();
				//mesaj de duel castigat ??
			}
			else if (m_duelStatus == DuelStatus::Lose)
			{
				// mesaj de duel pierdut ??
			}
			duelFinished = true;
			startDuel();
		}
	}
}

void TriviadorGame::checkMapWindowClosed()
{
	if (changePhase == true || serverAproveStatus == false) // daca o faza s-a terminat , asteptam sa trecem la urmatoarea
	{
		return;
	}
	if (m_gamePhase == GamePhase::ChooseRegions && m_MapWindowClosed == true && !MapWindow->isVisible())
	{
		if (true) // daca nu mai sunt zone libere , verificare de la server
		{
			changePhase = true;
		}
		else
		{
			m_MapWindowClosed = false;
		}
	}
	else if (m_gamePhase == GamePhase::Duels && m_MapWindowClosed == false && m_duelStatus == DuelStatus::None && !MapWindow->isVisible())
	{
		m_QTypeVariantsWindow.reset(new QTypeVariantsWindow(this));
		m_QTypeVariantsWindow->setPlayer(m_player);
		m_QTypeVariantsWindow->show();
		m_VariantsWindowClosed = true;
		m_MapWindowClosed = true;
	}
}

void TriviadorGame::checkVariantsWindowClosed()
{
	if (m_VariantsWindowClosed == true && !m_QTypeVariantsWindow->isVisible() && !MapWindow->isVisible() && serverAproveStatus == true)
	{
		m_VariantsWindowClosed = false;
		m_duelStatus = DuelStatus::Draw; // statusul va fi primit de la server prin json sau prin response.status_code
		if (m_duelStatus == DuelStatus::Win)
		{
			// Request :: de modificat statusul la board  ??

			MapWindow->show(); // MapWindow->ShowWindowForXSeconds();
			//mesaj de duel castigat ??
			startDuel();
		}
		else if (m_duelStatus == DuelStatus::Lose)
		{
			// mesaj de duel pierdut ??
		}
		else if (m_duelStatus == DuelStatus::Draw)
		{
			m_QTypeNumericWindow.reset(new QTypeNumericWindow(this));
			m_QTypeNumericWindow->setPlayer(m_player);
			m_QTypeNumericWindow->show();
			// GUI :: deschidere fereastra cu intrebarea numerica => creare ordine si restabilirea  la duelStatus
		}
	}
}

void TriviadorGame::checkCurrentPhase()
{
	if (checkIfWindowsAreClosed() == false || serverAproveStatus == false)
	{
		return;
	}

	if (m_gamePhase == GamePhase::None && changePhase == true)
	{
		chooseBasePhase();
	}
	else if (m_gamePhase == GamePhase::ChooseBase && changePhase == true)
	{
		chooseRegionsPhase();
	}
	else if (m_gamePhase == GamePhase::ChooseRegions && changePhase == true)
	{
		duelsPhase();
	}
	else if (m_gamePhase == GamePhase::Duels && changePhase == true)
	{
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
