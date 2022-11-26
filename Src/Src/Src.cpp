#include <iostream>
#include "board.h"
#include"Player.h"
#include "QuestionManager.h"
#include"AnswerFiftyFifty.h"
#include "AnswerSugestion.h"
#include "FourCloseAnswers.h"

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
	Player test4("Mihai", "Stan");
	test4.setColor(Player::Color::Yellow);
	std::cout << test4;



	//test 5
	Zone z(Player::Color::Blue);
	Board b(3);
	b[{2, 2}] = z;
	std::cout << b;


	return 0;
	





}

