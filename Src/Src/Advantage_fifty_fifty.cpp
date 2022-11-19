
#include "Advantage_Fifty_Fifty.h"
#include<random>
Advantage_Fifty_Fifty::Advantage_Fifty_Fifty(std::string answer, std::array<std::string,4> variants)
{
    this->m_answer = answer;
    
    for (int i=0;i<variants.size();i++)
    {
        this->m_variants[i] = variants[i];
    }
}

bool Advantage_Fifty_Fifty::Advantage_used()
{
    if (m_used == true)
        return m_used;
}

bool Advantage_Fifty_Fifty::get_Advantage_Fifty_Fifty()
{
    return m_used;
}

std::array<std::string,2> Advantage_Fifty_Fifty::advantage_utility()
{
    std::array<std::string,2>answer_remain;
    std::random_device rde;
    std::mt19937 engr(rde());
    std::uniform_int_distribution<> distrt(0, m_variants.size() - 1);
    auto answer1 = m_variants[distrt(engr)];
    answer_remain.push_back(answer1);
    answer_remain.push_back(m_answer);
    return answer_remain;

}
