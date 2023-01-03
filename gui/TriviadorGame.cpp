#include "TriviadorGame.h"

TriviadorGame::TriviadorGame(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	MapWindow.reset(new Map(this));
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

void TriviadorGame::setPlayer(const std::shared_ptr<PlayerInstance>& player)
{
	m_player = player;
}

void TriviadorGame::chooseBasePhase()
{
	// Request :: intrebare numerica

	// GUI :: deschidere fereastra cu intrebarea numerica
	// fereastra va contine si butoane pentru a introduce un raspuns , care va fi trimis catre server pentru a crea ordinea
	m_QTypeNumericWindow = std::make_shared<QTypeNumericWindow>(new QTypeNumericWindow());
	m_QTypeNumericWindow->setPlayer(m_player);
	m_QTypeNumericWindow->show();

	QTimer* timer = new QTimer(this);
	timer->setInterval(500);
	QObject::connect(timer, &QTimer::timeout, this, &TriviadorGame::checkNumericWindowClosed);
	timer->start();
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
	if (!m_QTypeNumericWindow->isVisible())
	{
		MapWindow->setNumberOfInterractions(2);
		MapWindow->setPlayer(m_player);
		MapWindow->show();
	}
}
