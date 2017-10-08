#include "stdafx.h"
#include "Student.h"


Student::Student(std::string id) throw()
{
    this->m_id = id;
}

std::string Student::Id() const throw()
{
    return m_id;
}

std::vector<TimeSegment> Student::FreeTimes() const throw()
{
    return m_freeTimes;
}

void Student::AddFreeTime(TimeSegment aFreeTime) throw()
{
    std::vector<TimeSegment> result;
    bool login = false;
    for (auto m_freeTime : m_freeTimes)
    {
        if (aFreeTime.Combine(m_freeTime) == false)
        {
            if (aFreeTime < m_freeTime)
            {
                login = true;
                result.push_back(aFreeTime);
            }
            result.push_back(m_freeTime);
        }
    }
    if (login == false)
    {
        result.push_back(aFreeTime);
    }
    m_freeTimes = result;
}

Student::~Student()
{
}
