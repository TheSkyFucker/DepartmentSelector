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
    for (auto m_freeTime : m_freeTimes)
    {
        if (m_freeTime.Combine(aFreeTime))
        {
            return;
        }
    }
    m_freeTimes.push_back(aFreeTime);
}

Student::~Student()
{
}
