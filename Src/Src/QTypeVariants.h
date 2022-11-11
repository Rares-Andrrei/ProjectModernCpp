#pragma once
#include <string>
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

};