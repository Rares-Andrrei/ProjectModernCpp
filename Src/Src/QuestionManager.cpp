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

QuestionManager::QuestionManager(const std::string& fileQTypeVariants, const std::string& fileQTypeNumerical)
{
	readQTypeVariants(fileQTypeVariants);
	// de apelat si fucntia de add pt intrebar numerice
}

void QuestionManager::addQFiles(const std::string& fileQTypeVariants, const std::string& fileQTypeNumerical)
{
	readQTypeVariants(fileQTypeVariants);
	// de apelat si fucntia de add pt intrebar numerice
}

QTypeVariants QuestionManager::randQTypeVariants()
{
	srand(time(NULL));
	return m_qWithVariants[rand() % m_qWithVariants.size()];
}
