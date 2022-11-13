#include "QuestionManager.h"
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
			question.setAnswer(temporary);			
			question.setVariants(variants);
			m_qWithVariants.push_back(question);
		}
		return true;
	}
	return false;
}

void QuestionManager::readQTypeNumerical()
{
	std::string question;
	std::string answer;

	for (std::ifstream in{ "QTypeNumerical.txt" }; !in.eof();)
	{
		std::getline(in, question);
		std::getline(in, answer);
		auto answerInteger = std::stoi(answer);
		m_qNumerical.emplace_back(question, answerInteger);
	}
}

QuestionManager::QuestionManager(const std::string& fileQTypeVariants)
{
	readQTypeVariants(fileQTypeVariants);
	readQTypeNumerical();
}

void QuestionManager::addQFiles(const std::string& fileQTypeVariants)
{
	readQTypeVariants(fileQTypeVariants);
	readQTypeNumerical();
}

QTypeVariants QuestionManager::randQTypeVariants()
{
	srand(time(NULL));
	return m_qWithVariants[rand() % m_qWithVariants.size()];
}

QTypeNumerical QuestionManager::randQTypeNumerical()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, m_qNumerical.size() - 1);
	return m_qNumerical[distr(eng)];
}
