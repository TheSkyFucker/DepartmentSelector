#include "stdafx.h"
#include "TimeSegment.h"
#include <algorithm>


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

int TimeSegment::Day() const throw()
{
    return m_day;
}

int TimeSegment::Begin() const throw()
{
    return m_begin;
}

int TimeSegment::End() const throw()
{
    return m_end;
}

bool TimeSegment::Include(TimeSegment aSegment) const throw()
{
    return m_day == aSegment.Day() 
        && m_begin <= aSegment.Begin() 
        && m_end >= aSegment.End();
}

bool TimeSegment::Combine(TimeSegment aSegment) throw()
{
    //check status
    bool result = m_day == aSegment.Day()
        && !(m_end < aSegment.Begin() || m_begin > aSegment.End());
    
    //do combine
    if (result)
    {
        m_begin = std::min(m_begin, aSegment.Begin());
        m_end = std::max(m_end, aSegment.End());
    }
    
    //return 
    return result;
}

bool TimeSegment::operator<(const TimeSegment & aSegment) const throw()
{
    if (m_day != aSegment.Day())
    {
        return m_day < aSegment.Day();
    }
    if (m_begin != aSegment.Begin())
    {
        return m_begin < aSegment.Begin();
    }
    return m_begin < aSegment.End();
}

TimeSegment::~TimeSegment()
{
}
