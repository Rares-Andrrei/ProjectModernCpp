#define _CRT_SECURE_NO_WARNINGS
#include "MatchInfo.h"
#include <chrono>
#include <sstream>

std::string MatchInfo::getEndtime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(now);
    std::stringstream s(std::ctime(&end_time));
    std::string day, month, year, hour, aux;
    int cnt = 1;
    while (s)
    {
        switch (cnt)
        {
        case 3:
            s >> day;
            break;
        case 2:
            s >> month;
            break;
        case 4:
            s >> hour;
            break;
        case 5:
            s >> year;
            break;
        default:
            s >> aux;
            break;
        }
        cnt++;
    }
    return day + "/" + month + "/" + year + " " + hour;
}

MatchInfo::MatchInfo(std::string date, std::array<std::optional<std::string>, 4> ranking) : m_date{date}, m_ranking{ranking}
{
}

std::string MatchInfo::getDate() const
{
    return m_date;
}

void MatchInfo::setDate(std::string date)
{
    m_date = date;
}

std::string MatchInfo::getFirstPlace() const
{
    if (m_ranking[0].has_value())
    {
        return m_ranking[0].value();
    }
    return "-";
}

void MatchInfo::setFirstPlace(const std::string& nickname)
{
    m_ranking[0] = nickname;
}

std::string MatchInfo::getSecondPlace() const
{
    if (m_ranking[1].has_value())
    {
        return m_ranking[1].value();
    }
    return "-";
}

void MatchInfo::setSecondPlace(const std::string& nickname)
{
    m_ranking[1] = nickname;
}

std::string MatchInfo::getThirdPlace() const
{
    if (m_ranking[2].has_value())
    {
        return m_ranking[2].value();
    }
    return "-";
}

void MatchInfo::setThirdPlace(const std::string& nickname)
{
    m_ranking[2] = nickname;
}

std::string MatchInfo::getFourthPlace() const
{
    if (m_ranking[3].has_value())
    {
        return m_ranking[3].value();
    }
    return "-";
}

void MatchInfo::setFourthPlace(const std::string& nickname)
{
    m_ranking[3] = nickname;
}
