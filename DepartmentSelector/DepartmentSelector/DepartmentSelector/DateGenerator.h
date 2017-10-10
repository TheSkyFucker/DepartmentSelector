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
#include "Student.h"
#include "Department.h"

class Department;
class Student;

class DateGenerator
{
    std::vector<std::string> m_tags;
    std::vector<std::string> m_days;
    std::vector<std::string> m_segs;

public:


    //************************************
    // Method:    RandStudentId
    // FullName:  DateGenerator::RandStudentId
    // Access:    public 
    // Returns:   std::string
    // Qualifier: throw()
    //************************************
    std::string RandStudentId() throw();


    //************************************
    // Method:    RandDepartmentId
    // FullName:  DateGenerator::RandDepartmentId
    // Access:    public 
    // Returns:   std::string
    // Qualifier: throw()
    //************************************
    std::string RandDepartmentId() throw();


    //************************************
    // Method:    RandStudentFreeTimes
    // FullName:  DateGenerator::RandStudentFreeTimes
    // Access:    public 
    // Returns:   std::vector<TimeSegment>
    // Qualifier: throw()
    //************************************
    std::vector<TimeSegment> RandStudentFreeTimes() throw();


    //************************************
    // Method:    RandDepartmentSchedules
    // FullName:  DateGenerator::RandDepartmentSchedules
    // Access:    public 
    // Returns:   std::vector<TimeSegment>
    // Qualifier: throw()
    //************************************
    std::vector<TimeSegment> RandDepartmentSchedules() throw();


    //************************************
    // Method:    RandStudentTags
    // FullName:  DateGenerator::RandStudentTags
    // Access:    public 
    // Returns:   std::vector<std::string>
    // Qualifier: throw()
    //************************************
    std::vector<std::string> RandStudentTags() throw();
    

    //************************************
    // Method:    RandDepartmentTags
    // FullName:  DateGenerator::RandDepartmentTags
    // Access:    public 
    // Returns:   std::vector<std::string>
    // Qualifier: throw()
    //************************************
    std::vector<std::string> RandDepartmentTags() throw();

    
    //************************************
    // Method:    RandStudentApplications
    // FullName:  DateGenerator::RandStudentApplications
    // Access:    public 
    // Returns:   std::vector<std::string>
    // Qualifier: throw()
    // Parameter: Student & aStudent
    // Parameter: std::vector<Department> & departments
    //************************************
    std::vector<std::string> RandStudentApplications(Student &aStudent, std::vector<Department> &departments) throw();


    //************************************
    // Method:    RandDepartmentMemberLimit
    // FullName:  DateGenerator::RandDepartmentMemberLimit
    // Access:    public 
    // Returns:   int
    // Qualifier: throw()
    //************************************
    int RandDepartmentMemberLimit() throw();


    //************************************
    // Method:    RandDepartment
    // FullName:  DateGenerator::RandDepartment
    // Access:    public 
    // Returns:   Department
    // Qualifier: throw()
    //************************************
    Department RandDepartment() throw();


    //************************************
    // Method:    RandStudent
    // FullName:  DateGenerator::RandStudent
    // Access:    public 
    // Returns:   Student
    // Qualifier: throw()
    // Parameter: std::vector<Department> departments
    //************************************
    Student RandStudent(std::vector<Department> departments) throw();


    DateGenerator();


    ~DateGenerator();
};

