﻿//===============================================================
//Summary:
//          TimeSegment 类， 
//FileName:
//          TimeSegment.h
//Remarks:
//          ...
//Date:
//          2017/10/7
//===============================================================

#pragma once
#include <vector>

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
    // Method:    TimeSegment
    // FullName:  TimeSegment::TimeSegment
    // Access:    public 
    // Returns:   
    // Qualifier:
    // Parameter: int _day
    // Parameter: int _begin
    // Parameter: int _end
    //************************************
    TimeSegment(int _day, int _begin, int _end);


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


    //************************************
    // Method:    operator<
    // FullName:  TimeSegment::operator<
    // Access:    public 
    // Returns:   bool
    // Qualifier: const throw()
    // Parameter: const TimeSegment & aSegment
    //************************************
    bool operator <(const TimeSegment &aSegment) const throw();


    //************************************
    // Method:    Cut
    // FullName:  TimeSegment::Cut
    // Access:    public 
    // Returns:   void
    // Qualifier: throw()
    // Parameter: TimeSegment aSegment
    //************************************
    std::vector<TimeSegment> Cut(TimeSegment aSegment) throw();


    //************************************
    // Method:    ToString
    // FullName:  TimeSegment::ToString
    // Access:    public 
    // Returns:   std::string
    // Qualifier: throw()
    //************************************
    std::string ToString() throw();

    ~TimeSegment();


};

