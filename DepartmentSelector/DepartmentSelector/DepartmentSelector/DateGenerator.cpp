#include "stdafx.h"
#include "DateGenerator.h"
#include <set>
#include <map>
#include <ctime>
#include <algorithm>


std::string DateGenerator::RandStudentId() throw()
{
    //config
    //srand((unsigned)time(0));
    std::string result;

    //院系：2位 [00, 99]
    result += '0' + rand() % 10;
    result += '0' + rand() % 10;

    //年份：2位 [16, 18]
    result += '1';
    result += '6' + rand() % 3;

    //专业：2位 [00, 99]
    result += '0' + rand() % 10;
    result += '0' + rand() % 10;

    //班级：1位 [0, 9]
    result += '0' + rand() % 10;

    //编号：2位 [0, 99]
    result += '0' + rand() % 10;
    result += '0' + rand() % 10;

    //return
    return result;
}

std::string DateGenerator::RandDepartmentId() throw()
{
    //config
    //srand((unsigned)time(0));
    std::string result = "D";
    
    //编号： 3位 [0, 999]
    result += '0' + rand() % 10;
    result += '0' + rand() % 10;
    result += '0' + rand() % 10;

    //return
    return result;
}

std::vector<TimeSegment> DateGenerator::RandStudentFreeTimes() throw()
{
    //config
    //srand((unsigned)time(0));
    std::vector<TimeSegment> result;
    size_t resultSize = 6 + rand() % 10;

    //rand
    std::set<std::string> segSet;
    while (result.size() < resultSize)
    {
        size_t _day = rand() % m_days.size();
        size_t _seg = rand() % m_segs.size();
        std::string tempSeg = m_days[_day] + m_segs[_seg];
        if (segSet.find(tempSeg) == segSet.end())
        {
            segSet.insert(tempSeg);
            result.push_back(TimeSegment(tempSeg));
        }
    }

    //return
    return result;
}

std::vector<TimeSegment> DateGenerator::RandDepartmentSchedules() throw()
{
    //config
    //srand((unsigned)time(0));
    std::vector<TimeSegment> result;
    size_t resultSize = 2 + rand() % 3;

    //rand
    std::set<std::string> segSet;
    while (result.size() < resultSize)
    {
        size_t _day = rand() % m_days.size();
        size_t _seg = rand() % m_segs.size();
        std::string tempSeg = m_days[_day] + m_segs[_seg];
        if (segSet.find(tempSeg) == segSet.end())
        {
            segSet.insert(tempSeg);
            TimeSegment aTempSeg(tempSeg);
            TimeSegment aRealSeg(aTempSeg.Day(), aTempSeg.Begin() + (rand() % 30), aTempSeg.End() - (rand() % 30));
            result.push_back(aRealSeg);
        }
    }

    //return
    return result;
}

std::vector<std::string> DateGenerator::RandStudentTags() throw()
{
    //config
    //srand((unsigned)time(0));
    std::vector<std::string> result;
    size_t resultSize = 6 + rand() % 10;

    //prework
    std::vector<int> indexs;
    for (size_t i = 0; i < m_tags.size(); i++)
    {
        indexs.push_back(i);
    }

    //rand
    std::set<std::string> tagSet;
    while (result.size() < resultSize)
    {
        size_t _index = rand() % indexs.size();
        int index = indexs[_index];
        if (tagSet.find(m_tags[index]) == tagSet.end())
        {
            tagSet.insert(m_tags[index]);
            result.push_back(m_tags[index]);
        }
        std::swap(indexs[_index], indexs.back());
        indexs.pop_back();
    }
    
    //return
    return result;
}

std::vector<std::string> DateGenerator::RandDepartmentTags() throw()
{
    //config
    //srand((unsigned)time(0));
    std::vector<std::string> result;
    size_t resultSize = 4 + rand() % 7;

    //prework
    std::vector<int> indexs;
    for (size_t i = 0; i < m_tags.size(); i++)
    {
        indexs.push_back(i);
    }

    //rand
    std::set<std::string> tagSet;
    while (result.size() < resultSize)
    {
        size_t _index = rand() % indexs.size();
        int index = indexs[_index];
        if (tagSet.find(m_tags[index]) == tagSet.end())
        {
            tagSet.insert(m_tags[index]);
            result.push_back(m_tags[index]);
        }
        std::swap(indexs[_index], indexs.back());
        indexs.pop_back();
    }

    //return
    return result;
}


std::vector<std::string> DateGenerator::RandStudentApplications(Student &aStudent, std::vector<Department> &departments) throw()
{
    //config
    //srand((unsigned)time(0));
    std::vector<std::string> result;
    std::vector<std::pair<double, std::string> > dptList;
    size_t resultSize = 3 + rand() % 3;

    //sort
    for (auto department : departments)
    {
        double dptValue = department.GetStudentValue(aStudent);
        if (department.IsConflict(aStudent))
        {
            dptValue -= 3.0;
        }
        dptList.push_back(std::make_pair(dptValue, department.Id()));
    }
    std::sort(dptList.begin(), dptList.end());

    //choose
    while (dptList.empty() == false && result.size() < resultSize)
    {
        result.push_back(dptList.back().second);
        dptList.pop_back();
    }

    //return 
    return result;
}

int DateGenerator::RandDepartmentMemberLimit() throw()
{
    //config    
    const int BIG_PERCENT = 30; //大部门（校级部门）比率

    //rand 
    int type = rand() % 100;
    if (type < BIG_PERCENT)
    {
        return 10 + rand() % 6;
    }
    else
    {
        return 7 + rand() % 6;
    }
}

Department DateGenerator::RandDepartment() throw()
{
    //config 
    Department result(RandDepartmentId());

    //rand tags
    auto tags = RandDepartmentTags();
    for (auto tag : tags)
    {
        result.AddTag(tag);
    }

    //rand schedules
    auto schedules = RandDepartmentSchedules();
    for (auto schedule : schedules)
    {
        result.AddSchedule(schedule);
    }

    //rand memberlimit
    result.SetMemberLimit(RandDepartmentMemberLimit());

    //return
    return result;
}

Student DateGenerator::RandStudent(std::vector<Department> departments) throw()
{
    //config
    Student result(RandStudentId());

    //rand tags
    auto tags = RandStudentTags();
    for (auto tag : tags)
    {
        result.AddTag(tag);
    }

    //rand freetimes

    for (auto freeTime : RandStudentFreeTimes())
    {
        result.AddFreeTime(freeTime);
    }

    //rand applications
    auto applications = RandStudentApplications(result, departments);
    for (auto application : applications)
    {
        result.AddApplication(application);
    }

    //return
    return result;
}


DateGenerator::DateGenerator()
{
    srand((unsigned)time(0));

    //init m_tags
    m_tags = std::vector<std::string>{
        "film", "English", "reading", "music", "dance", "basketball", "chess",
        "programming", "drawing", "writing", "football", "coding", "running",
        "moning", "testing", "talking", "food"
    };

    //init m_days && m_segs
    m_segs = std::vector<std::string>{ "08:20~10:00", "10:20~12:00", "14:00~15:40", "15:50~17:30", "19:00~20:40", "20:50~22:30" };
    m_days = std::vector<std::string>{ "Sun.", "Mon.", "Tues.", "Wed.", "Thur.", "Fri.", "Sat." };

}


DateGenerator::~DateGenerator()
{
}
