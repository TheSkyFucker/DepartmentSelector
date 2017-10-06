#include "stdafx.h"
#include "TimeSegment.h"




TimeSegment::TimeSegment(const std::string str)     //e.g Mon.16: 00~18 : 00
{

    //config
    const std::string DAY_TABLE[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    std::string aDay = str.substr(0, 3);
    std::string tmp = str.substr(str.find('.') + 1);

    //read
    std::pair<int, int> begin;
    std::pair<int, int> end;
    sscanf_s(tmp.c_str(), "%d: %d~%d: %d", &begin.first, &begin.second, &end.first, &end.second);

    //save
    for (int day = 0; day < 7; day++)
    {
        if (DAY_TABLE[day] == aDay)
        {
            m_day = day;
            break;
        }
    }
    m_begin = begin.first * 60 + begin.second;
    m_end = end.first * 60 + end.second;

}

int TimeSegment::GetDay()
{
    return m_day;
}

int TimeSegment::GetBegin()
{
    return m_begin;
}

int TimeSegment::GetEnd()
{
    return m_end;
}

bool TimeSegment::Include(TimeSegment aSeg)
{
    return m_day == aSeg.GetDay() && m_begin <= aSeg.GetBegin() && m_end >= aSeg.GetEnd();
}

TimeSegment::~TimeSegment()
{
}
