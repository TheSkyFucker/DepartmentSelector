//===============================================================
//Summary:
//          DateGenerator 类， 
//FileName:
//          DateGenerator.h
//Remarks:
//          ...
//Date:
//          2017/10/4
//===============================================================
#pragma once
#include <vector>
#include "TimeSegment.h"

class DateGenerator
{

    std::vector<std::string> m_tags;        //标签池
    std::vector<TimeSegment> m_timeSegments;//空闲时间池

    //************************************
    // Method:    InitTags
    // FullName:  DateGenerator::InitTags
    // Access:    private 
    // Returns:   void
    // Qualifier: throw()
    //************************************
    void InitTags() throw();

    //************************************
    // Method:    InitTimeSegments
    // FullName:  DateGenerator::InitTimeSegments
    // Access:    private 
    // Returns:   void
    // Qualifier: throw()
    //************************************
    std::vector<TimeSegment> RandStudentFreeTimes() throw();

public:

    //************************************
    // Method:    ChangeTags
    // FullName:  DateGenerator::ChangeTags
    // Access:    public 
    // Returns:   void
    // Qualifier: throw()
    // Parameter: std::vector<std::string> tags
    //************************************
    void ChangeTags(std::vector<std::string> tags) throw();

    DateGenerator();


    ~DateGenerator();
};

