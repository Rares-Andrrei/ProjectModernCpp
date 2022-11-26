#include "AnswerFiftyFifty.h"
#include<random>
AnswerFiftyFifty::AnswerFiftyFifty(QTypeVariants Q)
{
    this->m_answer = Q.getAnswer();
    m_variants.resize(4);
    std::array<std::string, 4>variants = Q.getVariants();
    for (int i = 0; i < variants.size(); i++)
    {
        this->m_variants[i] = variants[i];
    }
}

bool AnswerFiftyFifty::AdvantageUsed()
{
    if (m_used == true)
        return m_used;
}

bool AnswerFiftyFifty::getAdvantageFiftyFifty()
{
    return m_used;
}

std::vector<std::string> AnswerFiftyFifty::AdvantageUtility()
{
    auto f = std::find(m_variants.begin(), m_variants.end(), m_answer);
    m_variants.erase(f);
    std::vector<std::string>answerRemain;
    std::random_device rde;
    std::mt19937 engr(rde());
    std::uniform_int_distribution<> distrt(0, m_variants.size() - 1);
    auto answer1 = m_variants[distrt(engr)];
    if (answer1 != m_answer)
    {
        answerRemain.push_back(answer1);
        answerRemain.push_back("|");
        answerRemain.push_back(m_answer);
    }
    else
    {

    }
    m_used = true;
    return answerRemain;

}