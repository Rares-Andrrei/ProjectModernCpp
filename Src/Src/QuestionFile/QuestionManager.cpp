#include "QuestionManager.h"
#include "Database.h"
#include <fstream>
#include <random>


bool QuestionManager::readQTypeVariants(const std::string& fileQTypeVariants)
{
	const uint8_t numberOfVariants = 4;
	std::ifstream qFile(fileQTypeVariants);
	if (qFile.is_open())
	{
		QTypeVariants question;
		std::string temporary;
		std::array<std::string, 4> variants;
		std::getline(qFile, temporary);
		while (!qFile.eof())
		{
			std::getline(qFile, temporary);
			question.setQuestion(temporary);
			for ( uint8_t i = 0; i < numberOfVariants; i++)
			{
				std::getline(qFile, temporary);
				variants[i] = temporary;
			}
			std::getline(qFile, temporary);
			question.setVariants(variants);
			question.setAnswer(temporary);	
			m_qWithVariants.push_back(question);
		}
		qFile.close();
		return true;
	}
	return false;
}

void QuestionManager::readQTypeNumerical(const std::string& fileQTypeNumerical)
{
	std::string question;
	std::string answer;

	for (std::ifstream in{ fileQTypeNumerical }; !in.eof();)
	{
		if (in.is_open())
		{
			std::getline(in, question);
			std::getline(in, answer);
			auto answerInteger = std::stoi(answer);
			m_qNumerical.emplace_back(question, answerInteger);
		}
		else
		{
			std::string message = "The file doesn't opened";
			try
			{
				throw(message);
			}
			catch (std::string message) {
				std::cerr << "Error:" << message;
			}
		}
	}
}

QuestionManager::QuestionManager(const std::string& fileQTypeVariants, const std::string& fileQTypeNumerical)
{
	readQTypeVariants(fileQTypeVariants);
	readQTypeNumerical(fileQTypeNumerical);
}

void QuestionManager::addQFiles(const std::string& fileQTypeVariants, const std::string& fileQTypeNumerical)
{
	readQTypeVariants(fileQTypeVariants);
	readQTypeNumerical(fileQTypeNumerical);
}

void QuestionManager::pushQuestionsInDb(Database& db)
{
	db.insertQTypeVariants(m_qWithVariants);
	db.insertQTypeNumerical(m_qNumerical);
}

QTypeVariants QuestionManager::randQTypeVariants()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, m_qWithVariants.size() - 1);
	return m_qWithVariants[distr(eng)];
}

QTypeNumerical QuestionManager::randQTypeNumerical()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, m_qNumerical.size() - 1);
	return m_qNumerical[distr(eng)];
}