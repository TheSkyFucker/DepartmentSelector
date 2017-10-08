//===============================================================
//Summary:
//          Student 类， 
//FileName:
//          Student.h
//Remarks:
//          ...
//Date:
//          2017/10/4
//===============================================================
#pragma once
#pragma warning (disable:4290)
#include <vector>
#include "TimeSegment.h"

class Student
{

    std::string m_id;                               //学号
    //std::vector<std::string> m_applications;      //部门意愿

public:

    std::vector<std::string> m_tags;                //兴趣标签
    std::vector<TimeSegment> m_freeTimes;           //空闲时间
    std::vector<std::string> m_departments;         //中选部门


    //************************************
    // Method:    Student
    // FullName:  Student::Student
    // Access:    public 
    // Returns:   
    // Qualifier: throw()
    // Parameter: std::string id
    //************************************
    Student(std::string id) throw();


    //************************************
    // Method:    Id
    // FullName:  Student::Id
    // Access:    public 
    // Returns:   std::string
    // Qualifier: const throw()
    //************************************
    std::string Id() const throw();


    ~Student();
    
};

