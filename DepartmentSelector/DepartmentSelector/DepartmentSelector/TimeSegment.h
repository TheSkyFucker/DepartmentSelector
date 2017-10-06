#pragma once
class TimeSegment
{
    int m_day;      //星期[0..6]， 0代表周天
    int m_begin;    //开始时间戳，相对于 00:00
    int m_end;      //结束时间戳，相对于 00:00

public:


    //************************************
    // Method:    TimeSegment
    // FullName:  TimeSegment::TimeSegment
    // Access:    public 
    // Returns:   
    // Qualifier:
    // Parameter: std::string str
    //************************************
    TimeSegment(const std::string str);


    //************************************
    // Method:    GetDay
    // FullName:  TimeSegment::GetDay
    // Access:    public 
    // Returns:   int
    // Qualifier:
    //************************************
    int GetDay();


    //************************************
    // Method:    GetBegin
    // FullName:  TimeSegment::GetBegin
    // Access:    public 
    // Returns:   int
    // Qualifier:
    //************************************
    int GetBegin();


    //************************************
    // Method:    GetEnd
    // FullName:  TimeSegment::GetEnd
    // Access:    public 
    // Returns:   int
    // Qualifier:
    //************************************
    int GetEnd();


    //************************************
    // Method:    IsInclude
    // FullName:  TimeSegment::IsInclude
    // Access:    public 
    // Returns:   bool
    // Qualifier:
    // Parameter: TimeSegment
    //************************************
    bool Include(TimeSegment);

    ~TimeSegment();


};

