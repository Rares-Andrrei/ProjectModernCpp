#include "QTypeVariants.h"


QTypeVariants::QTypeVariants() : defaultAnswer{ "No answer found" }, m_id{-1}, m_answer{defaultAnswer}
{
}

void QTypeVariants::setQuestion(const std::string& question)
{
	this->m_question = question;
}

std::string QTypeVariants::getQuestion() const
{
	return m_question;
}

int QTypeVariants::getId() const
{
	return m_id;
}

void QTypeVariants::setId(int id)
{
	m_id = id;
}

void QTypeVariants::setAnswer(const std::string& answer)
{
	//se vor adauga mereu inainte variantele altfel nu functioneaza
	for (uint8_t i = 0;  i < m_variants.size();  i++)
	{
		if (answer == m_variants[i])
		{
			this->m_answer = m_variants[i];
		}
	}
}


QTypeVariants& QTypeVariants::operator=(const QTypeVariants& question)
{
	m_question = question.m_question;
	m_answer = question.m_answer;
	m_variants = question.m_variants;
	return *this;
}

void QTypeVariants::setVariants(const std::array<std::string, 4>& variants)
{
	this->m_variants = variants;
}

std::string QTypeVariants::getAnswer() const
{
	return m_answer;
}

std::array<std::string, 4> QTypeVariants::getVariants()
{
	return m_variants;
}

std::ostream& operator<<(std::ostream& out, const QTypeVariants& q)
{
	out << q.m_question << '\n';
	for (int i = 0; i < q.m_variants.size(); i++)
	{
		out << q.m_variants[i] << "  |  ";
	}
	out << '\n';
	return out;
}
