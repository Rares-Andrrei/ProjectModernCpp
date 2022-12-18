#pragma once
#include <string>
#include <iostream>
#include <array>
class QTypeVariants
{
	//int m_id;
	std::string defaultAnswer;
	static const int maxVariantsNr = 3;
	std::string m_question;
	std::string m_answer;
	std::array<std::string, 4> m_variants;
public:
	QTypeVariants();
	/*int getId() const;
	void setId(int id);*/

	void setQuestion(const std::string& question);
	std::string getQuestion() const;
	void setAnswer(const std::string& answer);
	std::string getAnswer() const;

	template <int varnumber>
	void setVariant(const std::string& variant)
	{
		if (varnumber <= maxVariantsNr && varnumber >= 0)
		{
			m_variants[varnumber] = variant;
		}
	}

	template <int varnumber>
	std::string getVariant() const
	{
		if (varnumber <= maxVariantsNr && varnumber >= 0)
		{
			return m_variants[varnumber];
		}
		return "";
	}

	QTypeVariants& operator = (const QTypeVariants& quesiton);

	void setVariants(const std::array<std::string, 4>& variants);
	std::array<std::string, 4>getVariants();
	friend std::ostream& operator <<(std::ostream& out, const QTypeVariants& q); //afisare in consola temporar pana avem gui
};