#include "stdafx.h"
#include "JsonIO.h"


JsonIO::JsonIO()
{
}


JsonIO::~JsonIO()
{
}

void JsonIO::Read(std::string filePath) throw(std::exception)
{
    //open file
    std::ifstream in;
    in.open(filePath, std::ifstream::in);
    if (in.is_open() == false)
    {
        throw std::exception("Function(JsonIO::Read): open file failed");
    }

    //read json string
    std::string inputString;
    for (std::string line; getline(in, line); )
    {
        inputString.append(line + "\n");
    }
    in.close();

    //save string
    m_inputJson = inputString;
}

std::vector<Student> JsonIO::DecodeStudents() const throw(std::exception)
{
    //decode input json
    rapidjson::Document doc;
    doc.Parse<0>(m_inputJson.c_str());
    if (doc.HasParseError())
    {
        throw std::exception("Function(JsonIO::DecodeStudents): json format error.");
    }

    //check students format
    rapidjson::Value& jsonStudents = doc["students"];
    if (jsonStudents.IsArray() == false)
    {
        throw std::exception("Function(JsonIO::DecodeStudents): students should be an array.");
    }
    for (size_t i = 0; i < jsonStudents.Size(); i++)
    {
        rapidjson::Value& aStudent = jsonStudents[i];
        if (aStudent.IsObject() == false)
        {
            throw std::exception("Function(JsonIO::DecodeStudents): student should be an Object.");
        }
        if (aStudent.HasMember("free_time") == false || aStudent["free_time"].IsArray() == false)
        {
            throw std::exception("Function(JsonIO::DecodeStudents): student.freeTimes should be an array.");
        }
        if (aStudent.HasMember("student_no") == false ||  aStudent["student_no"].IsString() == false)
        {
            throw std::exception("Function(JsonIO::DecodeStudents): student.student_no should be a string.");
        }
        if (aStudent.HasMember("applications_department") == false || aStudent["applications_department"].IsArray() == false)
        {
            throw std::exception("Function(JsonIO::DecodeStudents): student.applications should be an array.");
        }
        if (aStudent.HasMember("tags") == false || aStudent["tags"].IsArray() == false)
        {
            throw std::exception("Function(JsonIO::DecodeStudents): student.tags should be an array.");
        }
    }

    //decode jsonStudents
    std::vector<Student> resultStudents;
    for (size_t i = 0; i < jsonStudents.Size(); i++)
    {
        //construct Student
        rapidjson::Value& aStudent = jsonStudents[i];
        Student tempStudent(aStudent["student_no"].GetString());

        //add freeTimes
        for (size_t j = 0; j < aStudent["free_time"].Capacity(); j++)
        {
            tempStudent.AddFreeTime(TimeSegment(aStudent["free_time"][j].GetString()));
        }

        //add applications
        for (size_t j = 0; j < aStudent["applications_department"].Capacity(); j++)
        {
            tempStudent.AddApplication(aStudent["applications_department"][j].GetString());
        }

        //add tags
        for (size_t j = 0; j < aStudent["tags"].Capacity(); j++)
        {
            tempStudent.AddTag(aStudent["tags"][j].GetString());
        }

        //
        resultStudents.push_back(tempStudent);
    }

    //return result
    return resultStudents;

}

