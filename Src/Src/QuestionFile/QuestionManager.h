#pragma once
#include <vector>
#include "QTypeVariants.h"
#include "QTypeNumerical.h"

class QuestionManager
{
	bool readQTypeVariants(const std::string& fileQTypeVariants);
	std::vector<QTypeVariants> m_qWithVariants;
	std::vector<QTypeNumerical> m_qNumerical;
	void readQTypeNumerical(const std::string& fileQTypeVariants);
public:
	QuestionManager() = default;
	QuestionManager(const std::string& fileQTypeVariants, const std::string& fileQTypeNumerical);
	void addQFiles(const std::string& fileQTypeVariants, const std::string& fileQTypeNumerical);
	QTypeVariants randQTypeVariants();
	QTypeNumerical randQTypeNumerical();
};