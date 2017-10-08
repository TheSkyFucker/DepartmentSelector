#include "stdafx.h"
#include "Department.h"
#include <algorithm>


Department::Department(std::string id) throw()
{
    m_id = id;
    m_memberLimit = -1;
}

std::string Department::GetId() const throw()
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
            m_students.push_back(m_tempStudents.back());
            m_tempStudents.pop_back();
        }
        return;
    }

    //TODO Logic Path 2: 执行淘汰算法
}

std::vector<Student*> Department::GetStudents() const throw()
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

double Department::GetStudentValue(const Student & aStudent) const throw()
{
    //get same tag
    int numberTag = 0;
    for (auto m_tag : m_tags)
    {
        bool has = false;
        for (auto studentTag : aStudent.m_tags)
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
    return numberTag / (1. + (double)aStudent.m_departments.size());
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

Department::~Department()
{
}