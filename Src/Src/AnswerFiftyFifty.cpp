#include "AnswerFiftyFifty.h"
#include<random>
AnswerFiftyFifty::AnswerFiftyFifty(std::string answer, std::array<std::string, 4> variants)
{
    this->m_answer = answer;
    m_variants.resize(4);
    for (int i = 0; i < variants.size(); i++)
    {
        this->m_variants[i] = variants[i];
    }
}

bool AnswerFiftyFifty::Advantage_used()
{
    if (m_used == true)
        return m_used;
}

bool AnswerFiftyFifty::get_Advantage_Fifty_Fifty()
{
    return m_used;
}

std::vector<std::string> AnswerFiftyFifty::Advantage_utility()
{
    auto f = std::find(m_variants.begin(), m_variants.end(), m_answer);
    m_variants.erase(f);
    std::vector<std::string>answer_remain;
    answer_remain.resize(2);
    std::random_device rde;
    std::mt19937 engr(rde());
    std::uniform_int_distribution<> distrt(0, m_variants.size() - 1);
    auto answer1 = m_variants[distrt(engr)];
    if (answer1 != m_answer)
    {
        answer_remain.push_back(answer1);
        answer_remain.push_back(m_answer);
    }
    else
    {

    }
    m_used = true;
    return answer_remain;

}