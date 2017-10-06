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
#include "Student.h"
#include "TimeSegment.h"

class Department
{

    std::string m_id;                       //部门编号
//    int m_memberLimit;                      //学生上限
//    std::vector<std::string> m_tags;        //兴趣标签
//    std::vector<Student *> m_students;      //部门正式成员

public:

    std::vector<Student *> m_tempStudents;  //部门候选成员
    std::vector<TimeSegment> m_schedules;   //活动时间

    //************************************
    // Method:    Department
    // FullName:  Department::Department
    // Access:    public 
    // Returns:   
    // Qualifier:
    // Parameter: std::string id
    //************************************
    Department(std::string id);


    //************************************
    // Method:    GetId
    // FullName:  Department::GetId
    // Access:    public 
    // Returns:   std::string
    // Qualifier:
    //************************************
    std::string GetId();


    //************************************
    // Method:    DeleteConflictStudents
    // FullName:  Department::DeleteConflictStudents
    // Access:    public 
    // Returns:   void
    // Qualifier:
    //************************************
    void DeleteConflictStudents();

    ~Department();


   

};

