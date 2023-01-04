#include "ManualTests.h"

void TestSmartPointers()
{
}

void testAnswerFiftyFifty(QuestionManager test)
{
	/// testarea clasei AnswerFiftyFifty
	QTypeVariants test3 = test.randQTypeVariants();
	std::cout << "3. Intrebare cu variante de raspuns aleasa random pe care se va folosi avatajul fifty-fifty:\n";
	std::cout << test3;
	AnswerFiftyFifty test1(test3);

	std::array<std::string, 3>a = test1.AdvantageUtility();
	std::cout << "Raspunsurile ramase dupa folosirea avantajului fiftyfifty:\n";
	for (auto& i : a)
	{
		std::cout << i << " ";
	}

	std::cout << std::endl << std::endl;
}

void testFourCloseAnswers()
{
	/// testarea clasei FourCloseAnswers
	QuestionManager test;
	FourCloseAnswers test2;
	QTypeNumerical intrebare;
	intrebare = test.randQTypeNumerical();

	std::cout << "4. Intrebare numerica aleasa random pe care se va folosi avantajul de generare a 4 variante de raspuns:\n";
	std::cout << intrebare;
	test2.GenerateVariants(intrebare);
	std::cout << "Variantele de raspuns generate: \n";
	std::cout << test2;
	std::cout << std::endl;

}

void testDatabase()
{

	Database db("DatabaseFile/file.db");
	Account ac("Rares", "raresandrei", "rrs");
	std::cout << db.loginUser(ac) << std::endl;
	std::cout << db.registeUser(ac) << std::endl;
	std::cout << db.loginUser(ac) << std::endl;
	std::list<MatchInfo> test = db.getMatchHistory(ac);
	std::cout << MatchInfo::getEndtime();
}

void testMatch(const int& numberOfPlayers)
{
	GameLogic game(numberOfPlayers);
	const char* user1 = "Rares";
	game.addPlayer(user1);
	const char* user2 = "Alex";
	game.addPlayer(user2);
	game.StartGame();
	game.EndGame();
}

void testQuest()
{
	QuestionManager test;
	test.addQFiles("QTypeVariants.txt", "QTypeNumerical.txt");
	Database db("file.db");
	test.pushQuestionsInDb(db);
	std::cout << db.randQTypeVariants();
	std::cout << db.randQTypeNumerical();
}
