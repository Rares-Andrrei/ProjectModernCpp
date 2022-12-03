#pragma once
#include <array>

#include "../QuestionFile/QTypeNumerical.h"

class FourCloseAnswers
{
private:
	bool m_used = false;
	std::array<int, 4> m_answers;

public:
	FourCloseAnswers() = default;
	void GenerateVariants(QTypeNumerical q);
	bool AdvantageIsUsed();
	friend std::ostream& operator << (std::ostream& out, FourCloseAnswers const& answers);
};

