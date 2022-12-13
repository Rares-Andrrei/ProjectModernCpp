#include <iostream>
#include <memory>

#include "Database.h"
#include "Player.h"
#include "Board.h"
#include "Duel.h"
#include "ChooseBase.h"
#include "QuestionManager.h"
#include "AnswerFiftyFifty.h"
#include "AnswerSugestion.h"
#include "FourCloseAnswers.h"

#include <crow.h>
#include "utils.h"

void TestSmartPointers()
{
	std::cout << "\nTest 1 : Shared_Ptr: \n";
	//std::vector<std::shared_ptr<Zone>> vect;
	//vect.resize(9,std::make_shared<Zone>());

	Board b;
	std::shared_ptr<Zone> z(std::make_shared < Zone >(Player::Color::Blue));
	std::shared_ptr<PlayerBase> p(std::make_shared < PlayerBase >(Player::Color::Red));
	std::cout << *z << ' ' << *p << '\n';
	b[{1, 1}] = z;
	b[{2, 0}] = p;
	std::cout << b;
	//vect[0] = z;
	//vect[1] = p;
	/*for (auto& it : vect)
	{
		std::cout << *it << ' ';
	}*/

	//std::cout << "\n\nTest 2 : Unique_Ptr: \n";
	//std::vector<std::unique_ptr<Zone>> vect1;
	//vect1.resize(9, std::make_unique<Zone>());
	//std::unique_ptr<Zone> z1(new Zone(Player::Color::Blue));
	//std::unique_ptr<PlayerBase> p1(new PlayerBase(Player::Color::Red));
	//std::cout << *z1 << ' ' << *p1 << '\n';
	////vect1[0] = z1;
	////vect1[1] = p1;
	//for (auto& it : vect)
	//{
	//	std::cout << *it << ' ';
	//}
}
//Functie testare Duel
void testDuel(QuestionManager questions)
{
	Player::Color p1 = Player::Color::Blue;
	std::shared_ptr<Zone> zone(std::make_shared<Zone>(Player::Color::Blue));
	Duel duel(p1, zone);
	duel.generateQuestion(questions); // ii  dam setul de intrebari 

	QTypeVariants q1 = duel.getQTypeVariants(); //luam intrebarea generata


	std::cout << q1;
	std::string rp1, rp2; //afisare in consola a intrebarii pana avem gui

	std::cout << "blue player answer:";
	std::getline(std::cin, rp1);
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
	//delete zone;
	std::cout << std::endl;
}
// functie testare ChooseBase
void testChooseBase(Board& b, QuestionManager questions)
{
	///am creat un obiect de tip ChooseBase pentru 2 jucatori
	ChooseBase yes(questions, 2);


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
	yes.setBaseZone(b);
	std::cout << std::endl;
	std::cout << "9. Afisarea hartii :";

	std::cout << b;
}
void testQuestionManager(QuestionManager test)
{
	/// testarea clasei QuestionManager
	/// afisarea unei intrebari random impreuna cu variantele de raspuns
	std::cout << "1. Alegere si afisare intrebare cu 4 variante de raspuns: \n";
	std::cout << test.randQTypeVariants();
	std::cout << std::endl;

	std::cout << "2. Alegere si afisare intrebare cu raspuns numeric: \n";
	std::cout << test.randQTypeNumerical();
	std::cout << std::endl;
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
void testPlayer()
{
	/// testarea clasei Player
	std::cout << "5. Adaugarea numelui si prenumelui jucatorului impreuna cu culoarea asociata:\n";
	Player test4("Mihai", "Stan");
	test4.setColor(Player::Color::Yellow);
	std::cout << test4;
	std::cout << std::endl << std::endl;


}
void testZoneSiBoard(QuestionManager questions)
{
	/// tetsarea clasei Zone si Board
	std::cout << "6. Afisarea hartii impreuna cu punerea unui jucator pe o anumita zona:";
	std::shared_ptr<Zone> z(std::make_shared<Zone>(Player::Color::Blue));
	Board b(3);
	b[{2, 2}] = z;
	std::cout << b;
	std::cout << std::endl;
	std::cout << "7. Testare Smart Pointers" << std::endl;

	std::cout << "7. verificare functie duel: \n";
	testDuel(questions);
	std::cout << std::endl;

	std::cout << "8. verificare functie de alegere baza: \n";
	Board d;
	testChooseBase(d, questions);

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
int main()
{
	Database db("DatabaseFile/file.db");
	crow::SimpleApp app;

	CROW_ROUTE(app, "/")([] {
		return "Hallo guys";
		});

	auto& verifyLoginInfo = CROW_ROUTE(app, "/verifylogininfo")
		.methods(crow::HTTPMethod::Put);

	verifyLoginInfo([&db](const crow::request& req) {

		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");
	auto passwordIter = bodyArgs.find("password");

	Account testAccount;
	testAccount.setPassword(passwordIter->second);
	testAccount.setUsername(usernameIter->second);

	bool result = db.loginUser(testAccount);
	if (result == false)
	{
		return crow::response(400);
	}
	else
	{
		return crow::response(200);
	}
		});


	auto& registerUser = CROW_ROUTE(app, "/register")
		.methods(crow::HTTPMethod::Put);

	registerUser([&db](const crow::request& req) {

		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto nicknameIter = bodyArgs.find("nickname");
	auto usernameIter = bodyArgs.find("username");
	auto passwordIter = bodyArgs.find("password");

	Account testAccount;
	testAccount.setNickName(nicknameIter->second);
	testAccount.setPassword(passwordIter->second);
	testAccount.setUsername(usernameIter->second);

	bool result = db.registeUser(testAccount);
	if (result == false)
	{
		return crow::response(400);
	}
	else
	{
		return crow::response(200);
	}
		});


	auto& validateUsername = CROW_ROUTE(app, "/validateusername")
		.methods(crow::HTTPMethod::Put);
	
	validateUsername([&db](const crow::request& req) {

		auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");

	bool result = db.checkUsername(usernameIter->second);
	if (result == true)
	{
		return crow::response(400);
	}
	else
	{
		return crow::response(200);
	}
		});
	
	app.port(18080).multithreaded().run();

	//QuestionManager questions;
	//Board b;
	//questions.addQFiles("QuestionFile/QTypeVariants.txt", "QuestionFile/QTypeNumerical.txt");
	//TestSmartPointers();
	//testQuestionManager(questions);
	//testAnswerFiftyFifty(questions);
	//testZoneSiBoard(questions);
	//testPlayer();
	//testChooseBase(b, questions);


	testDatabase();

	return 0;
}

