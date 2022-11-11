#pragma once
#include <vector>
#include <fstream>
#include "QTypeVariants.h"
class QuestionManager
{
	bool readQTypeVariants(std::ifstream fileQTypeVariants);
	std::vector<QTypeVariants> m_qWithVariants;
	// de adaugat inca un vector cu intrebari raspuns numeric
public:
	QuestionManager() = default;
	QuestionManager(std::ifstream fileQTypeVariants, std::ifstream fileQTypeNumerical);
	void addQFiles(std::ifstream fileQTypeVariants, std::ifstream fileQTypeNumerical);
	QTypeVariants randQTypeVariants();
};