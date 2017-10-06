#include "stdafx.h"
#include "Department.h"


Department::Department(std::string id)
{
    m_id = id;
}

std::string Department::GetId()
{
    return m_id;
}

void Department::DeleteConflictStudents()
{
    for (int _student = m_tempStudents.size() - 1; _student >= 0; _student --)
    {
        Student * student = m_tempStudents[_student];
        for (auto schedule : m_schedules)
        {
            bool ok = false;
            for (auto freeTime : student->m_freeTimes)
            {
                if (freeTime.Include(schedule))
                {
                    ok = true;
                    break;
                }
            }
            if (ok == false)
            {
                std::swap(m_tempStudents[_student], m_tempStudents.back());
                m_tempStudents.pop_back();
                break;
            }
        }
    }
    return;
}

Department::~Department()
{
}