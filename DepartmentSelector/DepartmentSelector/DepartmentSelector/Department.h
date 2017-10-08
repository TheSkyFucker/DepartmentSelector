//===============================================================
//Summary:
//          Department 类， 
//FileName:
//          Department.h
//Remarks:
//          ...
//Date:
//          2017/10/4
//===============================================================
#pragma once
#pragma warning (disable:4290)
#include "Student.h"
#include "TimeSegment.h"

class Department
{

    std::string m_id;                       //部门编号
    std::vector<Student *> m_students;      //部门正式成员
    int m_memberLimit;                      //学生上限

public:

    std::vector<Student *> m_tempStudents;  //部门候选成员
    std::vector<TimeSegment> m_schedules;   //活动时间                                            
    std::vector<std::string> m_tags;        //兴趣标签


    //************************************
    // Method:    Department
    // FullName:  Department::Department
    // Access:    public 
    // Returns:   
    // Qualifier: throw()
    // Parameter: std::string id
    //************************************
    Department(std::string id) throw();


    //************************************
    // Method:    GetId
    // FullName:  Department::GetId
    // Access:    public 
    // Returns:   std::string
    // Qualifier: const throw()
    //************************************
    std::string Id() const throw();



    //************************************
    // Method:    DeleteConflictStudents
    // FullName:  Department::DeleteConflictStudents
    // Access:    public 
    // Returns:   void
    // Qualifier: throw()
    //************************************
    void DeleteConflictStudents() throw();


    //************************************
    // Method:    SelectStudents
    // FullName:  Department::SelectStudents
    // Access:    public 
    // Returns:   void
    // Qualifier: throw(std::exception)
    // Lable:     unselected tempStudent will not be delete from m_tempStudents
    //************************************
    void SelectStudents() throw(std::exception);


    //************************************
    // Method:    Students
    // FullName:  Department::Students
    // Access:    public 
    // Returns:   std::vector<Student *>
    // Qualifier: const throw()
    //************************************
    std::vector<Student *> Students() const throw();


    //************************************
    // Method:    SetMemberLimit
    // FullName:  Department::SetMemberLimit
    // Access:    public 
    // Returns:   void
    // Qualifier: throw(std::exception)
    // Parameter: int aLimit
    //************************************
    void SetMemberLimit(int aLimit) throw(std::exception);


    //************************************
    // Method:    GetStudentValue
    // FullName:  Department::GetStudentValue
    // Access:    public 
    // Returns:   double
    // Qualifier: const throw()
    // Parameter: const Student & aStudent
    //************************************
    double GetStudentValue(const Student &aStudent) const throw();


    //************************************
    // Method:    SortTempStudents
    // FullName:  Department::SortTempStudents
    // Access:    public 
    // Returns:   void
    // Qualifier: throw()
    //************************************
    void SortTempStudents() throw();


    ~Department();


   

};

