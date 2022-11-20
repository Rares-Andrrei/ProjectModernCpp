#include <iostream>
#include "Zone.h"
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
	QuestionManager test;
	test.addQFiles("QTypeVariants.txt", "QTypeNumerical.txt");
	std::cout << test.randQTypeVariants();
	std::cout << std::endl;
	std::cout << test.randQTypeNumerical();
	std::cout << std::endl;	
	AnswerFiftyFifty test1("Brazil", { "Colombia","Indonesia","Brazil","Vietnam" });//Testarea avantajului pentru intrebarea Which country produces the most coffee in the world?
	std::vector<std::string>a = test1.Advantage_utility();
	for (auto i : a)
	{
		std::cout << i << " ";
	}

	std::cout << std::endl << std::endl;

	FourCloseAnswers test2;
	QTypeNumerical intrebare;
	intrebare = test.randQTypeNumerical();
	std::cout << intrebare;
	test2.GenerateVariants(intrebare);
	std::cout << "generated variants: ";
	std::cout << test2;

	return 0;
	





}

