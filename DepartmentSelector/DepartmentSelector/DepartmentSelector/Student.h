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
#include <vector>

class Student
{

    std::string m_id;                           //学号
    //std::vector<std::string> m_tags;            //兴趣标签
    //std::vector<std::string> m_freeTimes;       //空闲时间
    //std::vector<std::string> m_applications;    //部门意愿

public:

    //************************************
    // Method:    Student
    // FullName:  Student::Student
    // Access:    public 
    // Returns:   
    // Qualifier:
    // Parameter: std::string id
    //************************************
    Student(std::string id);


    //************************************
    // Method:    GetId
    // FullName:  Student::GetId
    // Access:    public 
    // Returns:   std::string
    // Qualifier:
    //************************************
    std::string GetId();


    ~Student();
    
};

