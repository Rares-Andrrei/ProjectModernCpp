#include <iostream>
#include "board.h"
#include"Player.h"
#include "QuestionManager.h"
#include"AnswerFiftyFifty.h"
#include "AnswerSugestion.h"
#include "FourCloseAnswers.h"
#include "Duel.h"
#include "ChooseBase.h"


//Functie testare Duel
void testDuel()
{
	QuestionManager questions;
	questions.addQFiles("QTypeVariants.txt", "QTypeNumerical.txt");
	Player::Color p1 = Player::Color::Blue;
	Zone* zone = new Zone(Player::Color::Green);
	Duel duel(p1, zone);
	duel.generateQuestion(questions); // ii  dam setul de intrebari 

	QTypeVariants q1 = duel.getQTypeVariants(); //luam intrebarea generata


	std::cout << q1;
	std::string rp1, rp2; //afisare in consola a intrebarii pana avem gui

	std::cout << "blue player answer:";
	std::getline(std::cin,  rp1);
	std::cout << "green player answer:";
	std::getline(std::cin, rp2); //citire din consola a raspunsurilor pana avem gui

	duel.giveAnswers(rp1, rp2); //functie care ia raspunsurile

	if (duel.getWinner() == Player::Color::None && duel.isDraw()) //daca este None inseamna ca a fost remiza si trebuie sa mai generam o intrebare de tip numeric sa stabilim castigatorul
	{

		duel.generateQuestion(questions); //generam iar intrebare, functia stie daca a fost remiza si va genera intrebare de tip numeric de data asta.
		QTypeNumerical q2 = duel.getQTypeNumerical();

		std::cout << q2; //afisare in consola a intrebarii pana avem gui
		int rpi1, rpi2; 
		std::cin >> rpi1 >> rpi2; //citire din consola a raspunsurilor pana avem gui

		duel.giveAnswers(rpi1, rpi2); //trebuie modificata, voi lua ca parametrii un pair cu raspunsul si timpul in care au raspuns si in fucntie de asta o sa se decida castigatoru final
	}
	std::cout << int(duel.getWinner()) << std::endl; //putem returna culoarea castigatorului, functia poate fi folosita pt afisare in interfata grafica

	duel.rewardWinner(); //in fucntie de castigator functia schimba proprietarul zonei / adauga puncte zonei/ scade puncte zonei.

	std::cout << "Zona: " << int(zone->getColor()) << " " << zone->getScore();
	delete zone;
	std::cout << std::endl;
}

// functie testare ChooseBase
void testChooseBase()
{
	///am generat toate intrebarile 
	QuestionManager questions;
	questions.addQFiles("QTypeVariants.txt", "QTypeNumerical.txt");

	///am creat un obiect de tip ChooseBase pentru 2 jucatori
	ChooseBase yes(2);
	yes.ChooseAndPrintNumericalQuestion(questions);

	///am creat doua obiecte pentru jucatori
	Player::Color p1 = Player::Color::Blue;
	Player::Color p2 = Player::Color::Yellow;

	/// pentru cei doi jucatori am preluat raspunsul dat in consola si am facut ordinea in care acestia vor alege
	/// bazele
	int playerAnswer;
	std::cout << "Blue player answer: ";
	std::cin >> playerAnswer;
	yes.CreateOrder(p1, playerAnswer);
	std::cout << "Yellow player answer: ";
	std::cin >> playerAnswer;
	yes.CreateOrder(p2, playerAnswer);

	/// am setat clasa PlayerBase in ordinea raspunsurilor corecte
	yes.setBaseZone();
	std::cout << std::endl;
}


// TO DO: 
//  Creem clasa Player. citim un jucator si il afisam
//  Creem clasa Numeric Questions, citim o intrebare din fisier si o afisam
//  Creem clasa QuestionsWithFourAnswers , citim o intrebare din fisier si o afisam
//  Creem clasa Zone .O instantiem cu valorile necesare
//  Creem clasa Board , ce contine o matrice de Zone

int main()
{
/// testarea clasei QuestionManager
/// afisarea unei intrebari random impreuna cu variantele de raspuns
	QuestionManager test;
	test.addQFiles("QTypeVariants.txt", "QTypeNumerical.txt");

	return 0;
	





}

