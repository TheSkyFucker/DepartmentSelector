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
    // Method:    Day
    // FullName:  TimeSegment::Day
    // Access:    public 
    // Returns:   int
    // Qualifier: const throw()
    //************************************
    int Day() const throw();


    //************************************
    // Method:    Begin
    // FullName:  TimeSegment::Begin
    // Access:    public 
    // Returns:   int
    // Qualifier: const throw()
    //************************************
    int Begin() const throw();


    //************************************
    // Method:    End
    // FullName:  TimeSegment::End
    // Access:    public 
    // Returns:   int
    // Qualifier: const throw()
    //************************************
    int End() const throw();


    //************************************
    // Method:    Include
    // FullName:  TimeSegment::Include
    // Access:    public 
    // Returns:   bool
    // Qualifier: const throw()
    // Parameter: TimeSegment
    //************************************
    bool Include(TimeSegment aSegment) const throw();



    //************************************
    // Method:    Combine
    // FullName:  TimeSegment::Combine
    // Access:    public 
    // Returns:   bool
    // Qualifier: throw()
    // Parameter: TimeSegment aSegment
    // Lable:     有交则合并并返回true, 否则false
    //************************************
    bool Combine(TimeSegment aSegment) throw();

    ~TimeSegment();


};

