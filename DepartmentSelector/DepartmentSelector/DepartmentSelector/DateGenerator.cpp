#include "stdafx.h"
#include "DateGenerator.h"
#include <set>
#include <map>


void DateGenerator::InitTags() throw()
{
    //config
    const std::string tagsTable[] = {
        "film", "English", "reading", "music", "dance", "basketball", "chess",
        "programming", "drawing", "writing", "football"
    };

    //add
    std::set<std::string> tagsSet;
    for (auto aTag : tagsTable)
    {
        if (tagsSet.find(aTag) != tagsSet.end())
        {
            tagsSet.insert(aTag);
            m_tags.push_back(aTag);
        }
    }

}

std::vector<TimeSegment> DateGenerator::randStudentFreeTimes() throw()
{
    //config
    const std::string DAYS_TABLE[] = { "Sun.", "Mon.", "Tues", "Wed", "Fri", "Sat" };
    const std::string SEGS_TABLE[] = { "8: 20~10: 00", "10: 20~12: 00", "14: 00~15: 40", "15: 50~17:30", "19: 00~20: 40", "20: 50~22:30" };

    //add
    std::map
    for (auto aDay : DAYS_TABLE)
    {
        for (auto aSeg : SEGS_TABLE)
        {
            if (tagsSet.find(aTag) != tagsSet.end())
            {
                tagsSet.insert(aTag);
                m_tags.push_back(aTag);
            }
        }
    }
}

void DateGenerator::ChangeTags(std::vector<std::string> tags) throw()
{
    m_tags.clear();
    std::set<std::string> tagsSet;
    for (auto aTag : tags)
    {
        if (tagsSet.find(aTag) != tagsSet.end())
        {
            tagsSet.insert(aTag);
            m_tags.push_back(aTag);
        }
    }
}

DateGenerator::DateGenerator()
{
    //Init
    InitTags();
}


DateGenerator::~DateGenerator()
{
}
