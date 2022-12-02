#pragma once
#include <string>
#include <iostream>
#include <array>
class QTypeVariants
{
	std::string m_question;
	std::string m_answer;
	std::array<std::string, 4> m_variants;
public:
	QTypeVariants() = default;
	void setQuestion(const std::string& question);
	void setAnswer(const std::string& answer);
	void setVariants(const std::array<std::string, 4>& variants);
	std::string getAnswer() const;
	std::array<std::string, 4>getVariants() ;
	friend std::ostream& operator <<(std::ostream& out, const QTypeVariants& q); //afisare in consola temporar pana avem gui
};