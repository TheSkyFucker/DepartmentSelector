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
#include "include/rapidjson/prettywriter.h"
#include "include/rapidjson/stringbuffer.h"
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
    rapidjson::Document m_doc;



    //************************************
    // Method:    EncodeUnluckyStudents
    // FullName:  JsonIO::EncodeUnluckyStudents
    // Access:    public 
    // Returns:   rapidjson
    // Qualifier: throw()
    // Parameter: std::vector<Student> students
    //************************************
    rapidjson::Value EncodeUnluckyStudents(std::vector<Student> students) throw();


    //************************************
    // Method:    EncodeUnluckyDepartments
    // FullName:  JsonIO::EncodeUnluckyDepartments
    // Access:    private 
    // Returns:   rapidjson
    // Qualifier: throw()
    // Parameter: std::vector<Department> departments
    //************************************
    rapidjson::Value EncodeUnluckyDepartments(std::vector<Department> departments) throw();


    //************************************
    // Method:    EncodeLuckyDepartments
    // FullName:  JsonIO::EncodeLuckyDepartments
    // Access:    private 
    // Returns:   rapidjson
    // Qualifier: throw()
    // Parameter: std::vector<Department> departments
    //************************************
    rapidjson::Value EncodeLuckyDepartments(std::vector<Department> departments) throw();

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


    //************************************
    // Method:    DecodeDepartments
    // FullName:  JsonIO::DecodeDepartments
    // Access:    public 
    // Returns:   std::vector<Department>
    // Qualifier: const throw(std::exception)
    //************************************
    std::vector<Department> DecodeDepartments() const throw(std::exception);


    //************************************
    // Method:    EncodeSelectResult
    // FullName:  JsonIO::EncodeSelectResult
    // Access:    public 
    // Returns:   rapidjson
    // Qualifier: throw()
    // Parameter: std::vector<Student> students
    // Parameter: std::vector<Department> departments
    //************************************
    rapidjson::Value EncodeSelectResult(std::vector<Student> students, std::vector<Department> departments) throw();


    //std::string EncodeStudents(std::vector<Student> students) throw();
};

