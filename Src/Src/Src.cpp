#include <iostream>
#include "Zone.h"
#include"Player.h"
#include "QuestionManager.h"
#include"Advantage_Fifty_Fifty.h"
#include "AnswerSugestion.h"
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





}

