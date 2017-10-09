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
    std::vector<TimeSegment> m_freeTimes;           //空闲时间
    std::vector<std::string> m_tags;                //兴趣标签
    std::vector<std::string> m_departments;         //中选部门
    std::vector<std::string> m_applications;        //部门意愿

public:



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


    //************************************
    // Method:    FreeTimes
    // FullName:  Student::FreeTimes
    // Access:    public 
    // Returns:   std::vector<TimeSegment>
    // Qualifier: const throw()
    //************************************
    std::vector<TimeSegment> FreeTimes() const throw();


    //************************************
    // Method:    AddFreeTime
    // FullName:  Student::AddFreeTime
    // Access:    public 
    // Returns:   void
    // Qualifier: throw()
    // Parameter: TimeSegment aFreeTime
    //************************************
    void AddFreeTime(TimeSegment aFreeTime) throw();


    //************************************
    // Method:    Tags
    // FullName:  Student::Tags
    // Access:    public 
    // Returns:   std::vector<std::string>
    // Qualifier: throw()
    //************************************
    std::vector<std::string> Tags() throw();


    //************************************
    // Method:    addTag
    // FullName:  Student::addTag
    // Access:    public 
    // Returns:   void
    // Qualifier: throw()
    // Parameter: std::string aTag
    //************************************
    void AddTag(std::string aTag) throw();


    //************************************
    // Method:    Departments
    // FullName:  Student::Departments
    // Access:    public 
    // Returns:   std::vector<std::string>
    // Qualifier: const throw()
    //************************************
    std::vector<std::string> Departments() const throw();


    //************************************
    // Method:    AddDepartment
    // FullName:  Student::AddDepartment
    // Access:    public 
    // Returns:   void
    // Qualifier: throw()
    // Parameter: std::string aDepartment
    //************************************
    void AddDepartment(std::string aDepartment) throw();


    //************************************
    // Method:    Applications
    // FullName:  Student::Applications
    // Access:    public 
    // Returns:   std::vector<std::string>
    // Qualifier: const throw()
    //************************************
    std::vector<std::string> Applications() const throw();


    //************************************
    // Method:    AddApplication
    // FullName:  Student::AddApplication
    // Access:    public 
    // Returns:   void
    // Qualifier: throw()
    // Parameter: std::string aApplication
    //************************************
    void AddApplication(std::string aApplication) throw();

    ~Student();
    
};

