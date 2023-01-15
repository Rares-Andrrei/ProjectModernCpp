#pragma once
#include <array>
#include "../QuestionFile/QTypeNumerical.h"

class FourCloseAnswers
{
private:
	std::array<int, 4> m_answers;

public:
	FourCloseAnswers() = default;
	void GenerateVariants(QTypeNumerical q);
	std::array<int, 4> getAnswers();
	friend std::ostream& operator << (std::ostream& out, FourCloseAnswers const& answers);
};