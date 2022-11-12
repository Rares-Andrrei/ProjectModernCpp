#pragma once
#include <vector>
#include "QTypeVariants.h"
class QuestionManager
{
	bool readQTypeVariants(const std::string& fileQTypeVariants);
	std::vector<QTypeVariants> m_qWithVariants;
	// de adaugat inca un vector cu intrebari raspuns numeric
public:
	QuestionManager() = default;
	QuestionManager(const std::string& fileQTypeVariants, const std::string& fileQTypeNumerical);
	void addQFiles(const std::string& fileQTypeVariants, const std::string& fileQTypeNumerical);
	QTypeVariants randQTypeVariants();
};