//===============================================================
//Summary:
//          JsonIO 类， 
//FileName:
//          JsonIO.h
//Remarks:
//          ...
//Date:
//          2017/10/4
//===============================================================
#pragma once
#pragma warning (disable:4290)
#include "stdafx.h"
#include "include/rapidjson/rapidjson.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/reader.h"
#include "../DepartmentSelector/Student.h"
#include "../DepartmentSelector/Department.h"
#include "../DepartmentSelector/TimeSegment.h"
#include <fstream>
#include <string>
#include <cassert>
#include <iostream>

class JsonIO
{
    
    std::string m_inputJson; //输入数据缓存


public:
    JsonIO();
    ~JsonIO();

    //************************************
    // Method:    Read
    // FullName:  JsonIO::Read
    // Access:    public 
    // Returns:   void
    // Qualifier: throw(std::exception)
    // Parameter: std::string filePath
    //************************************
    void Read(std::string filePath) throw(std::exception);


    //************************************
    // Method:    DecodeStudents
    // FullName:  JsonIO::DecodeStudents
    // Access:    public 
    // Returns:   std::vector<Student>
    // Qualifier: const throw(std::exception)
    //************************************
    std::vector<Student> DecodeStudents() const throw(std::exception);


    std::vector<Department> DecodeDepartments() const throw(std::exception);
};

