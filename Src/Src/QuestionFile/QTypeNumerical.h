#pragma once
#include <string>
#include <iostream>

class QTypeNumerical
{
private:
	std::string m_question;
	int m_answer;
	int m_id;

public:
	QTypeNumerical() = default;
	QTypeNumerical(const std::string& question, int answer);

	int getId() const;
	void setId(int id);

	void setQuestion(const std::string& question);
	void setAnswer(const int& answer);
	std::string getQuestion() const;

	int getAnswer() const;

	friend std::ostream& operator <<(std::ostream& out, const QTypeNumerical& q);
};

