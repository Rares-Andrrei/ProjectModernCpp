#pragma once
#include <vector>
#include "QTypeVariants.h"
#include "QTypeNumerical.h"

class QuestionManager
{
	bool readQTypeVariants(const std::string& fileQTypeVariants);
	std::vector<QTypeVariants> m_qWithVariants;

	std::vector<QTypeNumerical> m_qNumerical;
	void readQTypeNumerical();
	// de adaugat inca un vector cu intrebari raspuns numeric
public:
	QuestionManager() = default;
	QuestionManager(const std::string& fileQTypeVariantsd);
	void addQFiles(const std::string& fileQTypeVariants);
	QTypeVariants randQTypeVariants();
	QTypeNumerical randQTypeNumerical();
};