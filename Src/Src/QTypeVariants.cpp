#include "QTypeVariants.h"

void QTypeVariants::setQuestion(const std::string& question)
{
	this->m_question = question;
}

void QTypeVariants::setAnswer(const std::string& answer)
{
	this->m_answer = answer;
}

void QTypeVariants::setVariants(const std::array<std::string, 4>& variants)
{
	this->m_variants = variants;
}

std::string QTypeVariants::getAnswer() const
{
	return m_answer;
}
