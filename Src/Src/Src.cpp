#include <iostream>
#include "board.h"
#include"Player.h"
#include "QuestionManager.h"
#include"AnswerFiftyFifty.h"
#include "AnswerSugestion.h"
#include "FourCloseAnswers.h"
#include "Duel.h"


//Functie testare duel
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

	std::getline(std::cin,  rp1);
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
}




// TO DO: 
//  Creem clasa Player. citim un jucator si il afisam
//  Creem clasa Numeric Questions, citim o intrebare din fisier si o afisam
//  Creem clasa QuestionsWithFourAnswers , citim o intrebare din fisier si o afisam
//  Creem clasa Zone .O instantiem cu valorile necesare
//  Creem clasa Board , ce contine o matrice de Zone

int main()
{
	//QuestionManager test;
	//test.addQFiles("QTypeVariants.txt", "QTypeNumerical.txt");
	//QTypeVariants test3 = test.randQTypeVariants();
	//std::cout << test3;

	//std::cout << std::endl;
	//std::cout << test.randQTypeNumerical();
	//std::cout << std::endl;	
	//AnswerFiftyFifty test1(test3);//Testarea avantajului pentru intrebarea Which country produces the most coffee in the world?
	//std::vector<std::string>a = test1.AdvantageUtility();
	//for (auto i : a)
	//{
	//	std::cout << i << " ";
	//}

	//std::cout << std::endl << std::endl;

	//FourCloseAnswers test2;
	//QTypeNumerical intrebare;
	//intrebare = test.randQTypeNumerical();
	//std::cout << intrebare;
	//test2.GenerateVariants(intrebare);
	//std::cout << "generated variants: ";
	//std::cout << test2;
	//Player test4("Mihai", "Stan");
	//test4.setColor(Player::Color::Yellow);
	//std::cout << test4;



	////test 5
	//Zone z(Player::Color::Blue);
	//Board b(3);
	//b[{2, 2}] = z;
	//std::cout << b;
	testDuel();

	return 0;
	





}

