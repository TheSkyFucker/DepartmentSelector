#include "stdafx.h"
#include "Department.h"
#include <algorithm>


void Department::AddStudent(Student * aStudent) throw(std::exception)
{
    if (m_students.size() == m_memberLimit)
    {
        throw std::exception("Function(Department::AddStudent): 非法使用，人数已达上限");
    }
    m_students.push_back(aStudent);
    aStudent->AddDepartment(m_id, m_schedules);
}

Department::Department(std::string id) throw()
{
    m_id = id;
    m_memberLimit = -1;
}

std::string Department::Id() const throw()
{
    return m_id;
}

void Department::DeleteConflictStudents() throw()
{
    for (int _student = m_tempStudents.size() - 1; _student >= 0; _student --)
    {
        Student * student = m_tempStudents[_student];
        for (auto schedule : m_schedules)
        {
            bool ok = false;
            for (auto freeTime : student->FreeTimes())
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

void Department::SelectStudents() throw(std::exception)
{
    //check m_memberLimit 
    if (!~m_memberLimit)
    {
        throw std::exception("Function(SelectStudent):未设置部门正式成员上限");
    }

    //去掉时间冲突学生
    DeleteConflictStudents();

    //Logic Path 1: 人数不超上限，全部中选
    int tot = (int)(m_students.size() + m_tempStudents.size());
    if (tot <= m_memberLimit)
    {
        while (m_tempStudents.empty() == false)
        {
            AddStudent(m_tempStudents.back());
            m_tempStudents.pop_back();
        }
        return;
    }

    //Logic Path 2: 执行淘汰算法
    SortTempStudents();
    while ((int)m_students.size() < m_memberLimit)
    {
        AddStudent(m_tempStudents.back());
        m_tempStudents.pop_back();
    }
    m_tempStudents.clear();

}

std::vector<Student*> Department::Students() const throw()
{
    return m_students;
}

void Department::SetMemberLimit(int aLimit) throw(std::exception)
{
    if (aLimit < 0)
    {
        throw std::exception("Funciton(SetMemberLimit):部门人数上限不能是负数");
    }
    if (aLimit < (int)m_students.size())
    {
        throw std::exception("Funciton(SetMemberLimit):部门人数上限不能少于当前正式成员数量");
    }
    m_memberLimit = aLimit;
}

double Department::GetStudentValue(Student & aStudent) const throw()
{
    //get same tag
    int numberTag = 0;
    for (auto m_tag : m_tags)
    {
        bool has = false;
        for (auto studentTag : aStudent.Tags())
        {
            if (studentTag == m_tag)
            {
                has = true;
                break;
            }
        }
        numberTag += has;
    }

    //count
    return numberTag / (1. + (double)aStudent.Departments().size());
}

void Department::SortTempStudents() throw()
{
    //get key value
    std::vector<std::pair<double, Student *> > result;
    for (auto student : m_tempStudents)
    {
        double value = GetStudentValue(*student);
        result.push_back(std::make_pair(value, student));
    }

    //sort
    std::sort(result.begin(), result.end());
    m_tempStudents.clear();
    for (auto elem : result)
    {
        m_tempStudents.push_back(elem.second);
    }
}

std::vector<TimeSegment> Department::Schedules() const throw()
{
    return m_schedules;
}

void Department::AddSchedule(TimeSegment aSchedule) throw()
{
    std::vector<TimeSegment> result;
    bool login = false;
    for (auto m_schedule : m_schedules)
    {
        if (aSchedule.Combine(m_schedule) == false)
        {
            if (aSchedule < m_schedule)
            {
                login = true;
                result.push_back(aSchedule);
            }
            result.push_back(m_schedule);
        }
    }
    if (login == false)
    {
        result.push_back(aSchedule);
    }
    m_schedules = result;
}



std::vector<std::string> Department::Tags() throw()
{
    return m_tags;
}

void Department::AddTag(std::string aTag) throw()
{
    for (auto tag : m_tags)
    {
        if (tag == aTag)
        {
            return;
        }
    }
    m_tags.push_back(aTag);
}

std::vector<Student*> Department::TempStudents() const throw()
{
    return m_tempStudents;
}

void Department::AddTempStudent(Student * aStudent) throw()
{
    //already in m_tempStudent
    for (auto m_tempStudent : m_tempStudents)
    {
        if (m_tempStudent->Id() == aStudent->Id())
        {
            return;
        }
    }

    //already in m_student
    for (auto m_student : m_students)
    {
        if (m_student->Id() == aStudent->Id())
        {
            return;
        }
    }

    //add
    m_tempStudents.push_back(aStudent);
}

Department::~Department()
{
}