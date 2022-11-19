
#include "Advantage_Fifty_Fifty.h"



Advantage_Fifty_Fifty::Advantage_Fifty_Fifty(std::string answer, std::vector<std::string> variants)
{
    this->m_answer = answer;
    variants.resize(4);
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
