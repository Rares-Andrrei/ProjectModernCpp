#pragma once
#include<string>
#include<vector>
#include<array>
class Advantage_Fifty_Fifty
{private:
	bool m_used = false;
	std::string m_answer;
	std::vector<std::string>m_variants;
    public:
	Advantage_Fifty_Fifty(std::string answer,std::array<std::string,4>variants);
	bool Advantage_used();
	bool get_Advantage_Fifty_Fifty();
	std::array<std::string,2>Advantage_utility();

};

