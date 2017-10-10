// Main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "JsonIO.h"
#include "../DepartmentSelector/DateGenerator.h"
#include "../DepartmentSelector/Student.h"
#include "../DepartmentSelector/Department.h"
#include <map>

/************************************************************************/
/* 全局参数                                                              */
/************************************************************************/
JsonIO myJsonIO;
std::vector<Department> departments;
std::vector<Student> students;
std::map<std::string, Department *> toDepartment;


/************************************************************************/
/* 职能：读取输入数据                                                      */
/************************************************************************/
void ReadJsonData()
{
    //config
    const std::string INPUT_FILE_PATH = "input_data.txt";
    
    //read
    myJsonIO.Read(INPUT_FILE_PATH);
    students = myJsonIO.DecodeStudents();
    departments = myJsonIO.DecodeDepartments();
}


/************************************************************************/
/* 职能：写入输出数据                                                      */
/************************************************************************/
void WriteJsonData()
{
    //config
    const std::string OUTPUT_FILE_PATH = "output_data.txt";
    freopen(OUTPUT_FILE_PATH.c_str(), "w", stdout);

    //write
    std::string data = myJsonIO.EncodeSelectResult(students, departments);
    std::cout << data << std::endl;
    
    //go back
    freopen("CON", "w", stdout);
}


/************************************************************************/
/* 职能：维护下一轮候选                                                    */
/************************************************************************/
void CreateDepartmentMap()
{
    for (int _department = 0; _department < (int)departments.size(); _department++)
    {
        toDepartment[departments[_department].Id()] = &departments[_department];
    }
}


/************************************************************************/
/* 职能：维护下一轮候选                                                    */
/************************************************************************/
void SubmitApplication(int round)
{
    for (int _student = 0; _student < (int)students.size(); _student++)
    {
        Student & student = students[_student];
        auto applications = student.Applications();
        if ((int)applications.size() >= round)
        {
            auto desDepartment = toDepartment[applications[round - 1]];
            desDepartment->AddTempStudent(&student);
        }
    }
}


/************************************************************************/
/* 职能：执行筛选                                                         */
/************************************************************************/
void SelectStudents()
{
    for (int _department = 0; _department < (int)departments.size(); _department++)
    {
        Department &department = departments[_department];
        department.SelectStudents();
    }
}


/************************************************************************/
/* 职能：总筛选流程                                                       */
/************************************************************************/
void DepartmentSelect(int argc, char * argv[])
{
    //config
    const int ROUND = 5; //round

    //read
    ReadJsonData();
    
    //创建部门Id索引表
    CreateDepartmentMap(); 

    //main
    for (int round = 1; round <= ROUND; round++)
    {
        SubmitApplication(round);
        SelectStudents();
    }

    //output
    WriteJsonData();
    
}


/************************************************************************/
/* 主代码                                                                */
/* 职能：分析指令                                                         */
/************************************************************************/
int main(int argc, char * argv[])
{

    DateGenerator gen;

    return 0;


    //work
    try
    {
        if (argc < 2) //默认指令，执行匹配
        {
            DepartmentSelect(argc, argv);
        }
    }
    catch (const std::exception& e)
    {
        puts(e.what());
    }

    return 0;
}

