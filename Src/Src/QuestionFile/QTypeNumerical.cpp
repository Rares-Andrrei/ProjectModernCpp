#include "QTypeNumerical.h"

QTypeNumerical::QTypeNumerical(const std::string& question, int answer)
	:m_question{ question }, m_answer{ answer }
{
}

int QTypeNumerical::getId() const
{
	return m_id;
}

void QTypeNumerical::setId(int id)
{
	m_id = id;
}

void QTypeNumerical::setQuestion(const std::string& question)
{
	m_question = question;
}

void QTypeNumerical::setAnswer(const int& answer)
{
	m_answer = answer;
}

std::string QTypeNumerical::getQuestion() const
{
	return m_question;
}

int QTypeNumerical::getAnswer() const
{
	return m_answer;
}

std::ostream& operator<<(std::ostream& out, const QTypeNumerical& q)
{
	out << q.m_question << std::endl;
	return out;
}
