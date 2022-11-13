#pragma once
#include <string>
#include <iostream>

class QTypeNumerical
{
private:
	std::string m_question;
	int m_answer;

public:
	QTypeNumerical() = default;
	QTypeNumerical(const std::string& question, int answer);

	void setQuestion(const std::string& question);
	void setAnswer(const int& answer);

	int getAnswer()const;

	friend std::ostream& operator <<(std::ostream& out, const QTypeNumerical& q);
};

