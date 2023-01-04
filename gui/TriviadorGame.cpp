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
	m_player = std::make_shared<PlayerQString>(player->getName());
	MapWindow->setPlayer(m_player);
}

void TriviadorGame::showEvent(QShowEvent* event)
{
	t_checkCurrentPhase->start();
	this->hide();
}

void TriviadorGame::chooseBasePhase()
{
	// Request :: intrebare numerica

	// GUI :: deschidere fereastra cu intrebarea numerica
	// fereastra va contine si butoane pentru a introduce un raspuns , care va fi trimis catre server pentru a crea ordinea
	m_QTypeNumericWindow.reset(new QTypeNumericWindow(this));
	m_QTypeNumericWindow->setPlayer(m_player);
	m_QTypeNumericWindow->show();


	// GUI :: inchidere fereastra cu intrebarea numerica

	// GUI :: deschidere fereastra cu harta
	//MapWindow->show(); // clientul va trebui sa aibe access la butoane doar atunci cand primeste un raspuns pozitiv de la server
	// GUI :: inchidere fereastra cu harta
}

void TriviadorGame::chooseRegionsPhase()
{
	while (true)
	{
		// Request :: intrebare numerica

		// GUI :: deschidere fereastra cu intrebarea numerica
		// fereastra va contine si butoane pentru a introduce un raspuns , care va fi trimis catre server pentru a crea ordinea
		// GUI :: inchidere fereastra cu intrebarea numerica

		// GUI :: deschidere fereastra cu harta
		MapWindow->show();
		while (true)
		{
			// clientul va trebui sa aibe access la butoane doar atunci cand primeste un raspuns pozitiv de la server
			// clientul va trebui sa aleaga atatea regiuni cate serverul ii spune , cat timp exista zone libere
		}
		// GUI :: inchidere fereastra cu harta
	}
}

void TriviadorGame::duelsPhase()
{
	uint16_t maxNumberOfDuels = 5;
	if (m_numberOfPlayers == 2)
		maxNumberOfDuels = 4;

	int numberOfDuels = 0;
	while (numberOfDuels < maxNumberOfDuels)
	{
		bool allPlayersPlayed = false;
		// Request :: verificare fiecare jucator ACTIV a jucat runda de duel ( fiecare jucator trebuie sa se dueleze 1 data per runda de duel )
		if (allPlayersPlayed == true)
			numberOfDuels++;
		if (numberOfDuels == maxNumberOfDuels)
			break;

		// Request :: intrebare cu raspunsuri multiple
		// GUI :: deschidere fereastra cu intrebarea cu raspunsuri multiple
		// GUI :: inchidere fereastra cu intrebarea cu raspunsuri multiple
		// Request :: verificare status duel ( daca a fost castigat SAU nu SAU daca a fost egalitate SI ambii au ales corect )
		TriviadorGame::DuelStatus duelStatus = TriviadorGame::DuelStatus::Win; // statusul va fi primit de la server prin json sau prin response.status_code

		if (duelStatus == TriviadorGame::DuelStatus::Win)
		{
			// Request :: de modificat statusul la board  ??
			// GUI :: deschidere fereastra cu harta pentru a se vedea cum zona a fost castigata , in cazul in care sunt indeplinite conditiile
			MapWindow->show();
			//mesaj de duel castigat ??
		}
		else if (duelStatus == TriviadorGame::DuelStatus::Lose)
		{
			// mesaj de duel pierdut ??
		}
		else if (duelStatus == TriviadorGame::DuelStatus::Draw)
		{
			// Request :: intrebare numerica 
			// GUI :: deschidere fereastra cu intrebarea numerica => creare ordine si restabilirea  la duelStatus
			// GUI :: inchidere fereastra cu intrebarea numerica\
			// serverul va  face toate operatiile din spate si determinarea daca harta se modifica
			duelStatus = TriviadorGame::DuelStatus::Lose; // statusul va fi primit de la server prin json sau prin response.status_code , poate fi doar WIN sau LOSE , DRAW = LOSE
			if (duelStatus == TriviadorGame::DuelStatus::Win)
			{
				// Request :: de modificat statusul la board  ??
				// GUI :: deschidere fereastra cu harta pentru a se vedea cum zona a fost castigata , in cazul in care sunt indeplinite conditiile
				MapWindow->show();
				//mesaj de duel castigat ??
			}
			else if (duelStatus == TriviadorGame::DuelStatus::Lose)
			{
				// mesaj de duel pierdut ??
			}
		}
	}
}

void TriviadorGame::EndGame()
{
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
	if (changePhase == true) // daca o faza s-a terminat , asteptam sa trecem la urmatoarea
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
		if (!m_QTypeNumericWindow->isVisible())
		{
			m_QTypeNumericWindow.reset();
			MapWindow->setNumberOfInterractions(m_numberOfPlayers * 2);
			MapWindow->show();
		}
	}
	else if (m_gamePhase == GamePhase::Duels && m_duelStatus == DuelStatus::Draw)
	{
		if (!m_QTypeNumericWindow->isVisible())
		{
			m_QTypeNumericWindow.reset();
			MapWindow->setNumberOfInterractions(1);
			MapWindow->show();
		}
	}
}

void TriviadorGame::checkMapWindowClosed()
{
}

void TriviadorGame::checkVariantsWindowClosed()
{
}

void TriviadorGame::checkCurrentPhase()
{
	if (checkIfWindowsAreClosed() == false)
	{
		return;
	}
	
	if (m_gamePhase == GamePhase::None && changePhase == true)
	{
		t_NumericWindowTimer->start();
		changePhase = false;
		m_gamePhase = GamePhase::ChooseBase;
		chooseBasePhase();
	}
	else if (m_gamePhase == GamePhase::ChooseBase && changePhase == true)
	{
		changePhase = false;
		m_gamePhase = GamePhase::ChooseRegions;
		chooseRegionsPhase();
	}
	else if (m_gamePhase == GamePhase::ChooseRegions && changePhase == true)
	{
		changePhase = false;
		m_gamePhase = GamePhase::Duels;
		t_VariantsWindowTimer->start();
		duelsPhase();
	}
	else if (m_gamePhase == GamePhase::Duels && changePhase == true)
	{
		changePhase = false;
		t_checkCurrentPhase->stop();

		t_MapWindowTimer->stop();
		t_VariantsWindowTimer->stop();
		t_NumericWindowTimer->stop();

		m_gamePhase = GamePhase::End;
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
