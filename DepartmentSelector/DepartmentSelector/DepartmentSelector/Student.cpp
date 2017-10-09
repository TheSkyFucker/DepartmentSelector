#include "stdafx.h"
#include "Student.h"


void Student::DeleteFreeTime(TimeSegment aSegment) throw()
{
    std::vector<TimeSegment> result;
    for (auto m_freeTime : m_freeTimes)
    {
        if (aSegment.Include(m_freeTime) == false)
        {
            //auto tmpSegs = m_freeTime.Cut()
            //TODO:
            //TODO:result.push_back(m_freeTime.Cut(aSegment));
        }
    }
}

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

std::vector<std::string> Student::Tags() throw()
{
    return m_tags;
}

void Student::AddTag(std::string aTag) throw()
{
    for (auto m_tag : m_tags)
    {
        if (m_tag == aTag)
        {
            return;
        }
    }
    m_tags.push_back(aTag);
}

std::vector<std::string> Student::Departments() const throw()
{
    return m_departments;
}

void Student::AddDepartment(std::string aDepartment, std::vector<TimeSegment> departmentSchedules) throw()
{

    //check
    for (auto m_department : m_departments)
    {
        if (m_department == aDepartment)
        {
            return;
        }
    }
    m_departments.push_back(aDepartment);

    //delete free time
    for (auto aSchedule : departmentSchedules)
    {
        DeleteFreeTime(aSchedule);
    }
}

std::vector<std::string> Student::Applications() const throw()
{
    return m_applications;
}

void Student::AddApplication(std::string aApplication) throw()
{
    m_applications.push_back(aApplication);
}

Student::~Student()
{
}
