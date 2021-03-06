﻿#include "stdafx.h"
#include "JsonIO.h"


std::string JsonIO::ChangeFormat(std::string aJson) throw()
{
    //config
    std::string result;

    //change
    int tabs = 0;
    for (size_t i = 0; i < aJson.size(); i++)
    {
        //check tabs
        if (aJson[i] == '[' || aJson[i] == '{')
        {
            tabs += 4;
        }
        else if (aJson[i] == ']' || aJson[i] == '}')
        {
            tabs -= 4;
        }
        
        //add tabs
        if (aJson[i] == '}' || aJson[i] == ']')
        {
            result += "\n";
            for (int j = 0; j < tabs; j++) result += " ";
            result += aJson[i];
        }
        else
        {
            result += aJson[i];
            if (aJson[i] == '[' || aJson[i] == '{' || aJson[i] == ',')
            {
                result += "\n";
                for (int j = 0; j < tabs; j++) result += " ";
            }
        }
    }

    //return 
    return result;
}

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

std::vector<Department> JsonIO::DecodeDepartments() const throw(std::exception)
{
    //decode input json
    rapidjson::Document doc;
    doc.Parse<0>(m_inputJson.c_str());
    if (doc.HasParseError())
    {
        throw std::exception("Function(JsonIO::DecodeDepartments): json format error.");
    }

    //check departments format
    rapidjson::Value& jsonDepartment = doc["departments"];
    if (jsonDepartment.IsArray() == false)
    {
        throw std::exception("Function(JsonIO::DecodeDepartments): departments should be an array.");
    }
    for (size_t i = 0; i < jsonDepartment.Size(); i++)
    {
        rapidjson::Value& aDepartment = jsonDepartment[i];
        if (aDepartment.IsObject() == false)
        {
            throw std::exception("Function(JsonIO::DecodeDepartments): department should be an object.");
        }
        if (aDepartment.HasMember("event_schedules") == false || aDepartment["event_schedules"].IsArray() == false)
        {
            throw std::exception("Function(JsonIO::DecodeDepartments): department.event_schedules should be an array.");
        }
        if (aDepartment.HasMember("member_limit") == false || aDepartment["member_limit"].IsInt() == false)
        {
            throw std::exception("Function(JsonIO::DecodeDepartments): department.member_limit should be an Int.");
        }
        if (aDepartment.HasMember("department_no") == false ||  aDepartment["department_no"].IsString() == false)
        {
            throw std::exception("Function(JsonIO::DecodeDepartments): department.department_no should be a string.");
        }
        if (aDepartment.HasMember("tags") == false || aDepartment["tags"].IsArray() == false)
        {
            throw std::exception("Function(JsonIO::DecodeDepartments): department.tags should be a string array.");
        }
    }

    //decode departments
    std::vector<Department> resultDepartments;
    for (size_t i = 0; i < jsonDepartment.Size(); i++)
    {
        //construct department 
        rapidjson::Value& aDepartment = jsonDepartment[i];
        Department tempDepartment(aDepartment["department_no"].GetString());

        //add event_schedules
        for (size_t j = 0; j < aDepartment["event_schedules"].Capacity(); j++)
        {
            TimeSegment aSchedule(aDepartment["event_schedules"][j].GetString());
            tempDepartment.AddSchedule(aSchedule);
        }

        //add member_limit
        tempDepartment.SetMemberLimit(aDepartment["member_limit"].GetInt());
    
        //add tags
        for (size_t j = 0; j < aDepartment["tags"].Capacity(); j++)
        {
            tempDepartment.AddTag(aDepartment["tags"][j].GetString());
        }

        //
        resultDepartments.push_back(tempDepartment);
    }

    //return
    return resultDepartments;
}

rapidjson::Value JsonIO::EncodeUnluckyStudents(std::vector<Student> students) throw()
{

    //config
    rapidjson::Document::AllocatorType & allocator = m_doc.GetAllocator();

    //encode
    rapidjson::Value jsonStudents(rapidjson::kArrayType);
    for (auto student : students)
    {
        rapidjson::Value id(rapidjson::kStringType);
        id.SetString(student.Id().c_str(), allocator);
        jsonStudents.PushBack(id, allocator);
    }

    //return
    return jsonStudents;
}

rapidjson::Value JsonIO::EncodeUnluckyDepartments(std::vector<Department> departments) throw()
{
    //config
    rapidjson::Document::AllocatorType & allocator = m_doc.GetAllocator();

    //encode
    rapidjson::Value jsonDepartments(rapidjson::kArrayType);
    for (auto department : departments)
    {
        rapidjson::Value id(rapidjson::kStringType);
        id.SetString(department.Id().c_str(), allocator);
        jsonDepartments.PushBack(id, allocator);
    }

    //return
    return jsonDepartments;
}

rapidjson::Value JsonIO::EncodeLuckyDepartments(std::vector<Department> departments) throw()
{
    //config
    rapidjson::Document::AllocatorType & allocator = m_doc.GetAllocator();

    //encode
    rapidjson::Value jsonDepartments(rapidjson::kArrayType);
    for (auto department : departments)
    {
        rapidjson::Value jsonDepartment(rapidjson::kObjectType);
        
        //get id
        rapidjson::Value id(rapidjson::kStringType);
        id.SetString(department.Id().c_str(), allocator);
        jsonDepartment.AddMember("department_no", id, allocator);
        
        //get member
        rapidjson::Value member(rapidjson::kArrayType);
        for (auto student : department.Students())
        {
            rapidjson::Value id(rapidjson::kStringType);
            id.SetString(student->Id().c_str(), allocator);
            member.PushBack(id, allocator);
        }
        jsonDepartment.AddMember("member", member, allocator);

        //save
        jsonDepartments.PushBack(jsonDepartment, allocator);
    }

    //return
    return jsonDepartments;
}

rapidjson::Value JsonIO::EncodeSelectResult(std::vector<Student> students, std::vector<Department> departments) throw()
{

    //config
    rapidjson::Value resultJson(rapidjson::kObjectType);
    rapidjson::Document::AllocatorType & allocator = m_doc.GetAllocator();
    
    //encode unlucky_students
    std::vector<Student> unluckyStudents;
    for (auto student : students)
    {
        if (student.Departments().size() < (size_t)1)
        {
            unluckyStudents.push_back(student);
        }
    }
    auto jsonUnluckyStudents = EncodeUnluckyStudents(unluckyStudents);    
    resultJson.AddMember("unlucky_student", jsonUnluckyStudents, allocator);
    
    //get (un)luckDepartments
    std::vector<Department> unluckyDepartments;
    std::vector<Department> luckyDepartments;
    for (auto department : departments)
    {
        if (department.Students().size() == (size_t)0)
        {
            unluckyDepartments.push_back(department);
        }
        else
        {
            luckyDepartments.push_back(department);
        }
    }
    
    //encode admitted
    auto jsonluckyDepartments = EncodeLuckyDepartments(luckyDepartments);
    resultJson.AddMember("admitted", jsonluckyDepartments, allocator);

    //encode unlucky_departments
    auto jsonUnluckyDepartments = EncodeUnluckyDepartments(unluckyDepartments);
    resultJson.AddMember("unlucky_department", jsonUnluckyDepartments, allocator);

    //return
    return resultJson;
}

rapidjson::Value JsonIO::EncodeStudents(std::vector<Student> students) throw()
{
    //config
    rapidjson::Document::AllocatorType & allocator = m_doc.GetAllocator();

    //encode
    rapidjson::Value jsonStudents(rapidjson::kArrayType);
    for (auto student : students)
    {
        rapidjson::Value jsonStudent(rapidjson::kObjectType);
        
        //encode student_no
        rapidjson::Value id(rapidjson::kStringType);
        id.SetString(student.Id().c_str(), allocator);
        jsonStudent.AddMember("student_no", id, allocator);
        
        //encode free_time
        rapidjson::Value jsonFreeTimes(rapidjson::kArrayType);
        for (auto aFreeTime : student.FreeTimes())
        {
            rapidjson::Value jsonTime(rapidjson::kStringType);
            jsonTime.SetString(aFreeTime.ToString().c_str(), allocator);
            jsonFreeTimes.PushBack(jsonTime, allocator);
        }
        jsonStudent.AddMember("free_time", jsonFreeTimes, allocator);

        //encode tags
        rapidjson::Value jsonTags(rapidjson::kArrayType);
        for (auto aTag : student.Tags())
        {
            rapidjson::Value jsonTag(rapidjson::kStringType);
            jsonTag.SetString(aTag.c_str(), allocator);
            jsonTags.PushBack(jsonTag, allocator);
        }
        jsonStudent.AddMember("tags", jsonTags, allocator);
        
        //encode applications_department
        rapidjson::Value jsonApplications(rapidjson::kArrayType);
        for (auto aApplication : student.Applications())
        {
            rapidjson::Value jsonApplication(rapidjson::kStringType);
            jsonApplication.SetString(aApplication.c_str(), allocator);
            jsonApplications.PushBack(jsonApplication, allocator);
        }
        jsonStudent.AddMember("applications_department", jsonApplications, allocator);

        //complete
        jsonStudents.PushBack(jsonStudent, allocator);
    }

    //return
    return jsonStudents;
}

rapidjson::Value JsonIO::EncodeDepartments(std::vector<Department> departments) throw()
{
    //config
    rapidjson::Document::AllocatorType & allocator = m_doc.GetAllocator();

    //encode
    rapidjson::Value jsonDepartments(rapidjson::kArrayType);
    for (auto department : departments)
    {
        rapidjson::Value jsonDepartment(rapidjson::kObjectType);

        //encode department_no
        rapidjson::Value jsonId(rapidjson::kStringType);
        jsonId.SetString(department.Id().c_str(), allocator);
        jsonDepartment.AddMember("department_no", jsonId, allocator);

        //encode member_limit
        rapidjson::Value jsonMemberLimit(rapidjson::kNumberType);
        jsonMemberLimit.SetInt(department.MemberLimit());
        jsonDepartment.AddMember("member_limit", jsonMemberLimit, allocator);

        //encode tags
        rapidjson::Value jsonTags(rapidjson::kArrayType);
        for (auto aTag : department.Tags())
        {
            rapidjson::Value jsonTag(rapidjson::kStringType);
            jsonTag.SetString(aTag.c_str(), allocator);
            jsonTags.PushBack(jsonTag, allocator);
        }
        jsonDepartment.AddMember("tags", jsonTags, allocator);

        //encode event_schedules
        rapidjson::Value jsonSchedules(rapidjson::kArrayType);
        for (auto aSchedule : department.Schedules())
        {
            rapidjson::Value jsonSchedule(rapidjson::kStringType);
            jsonSchedule.SetString(aSchedule.ToString().c_str(), allocator);
            jsonSchedules.PushBack(jsonSchedule, allocator);
        }
        jsonDepartment.AddMember("event_schedules", jsonSchedules, allocator);
        
        //complete
        jsonDepartments.PushBack(jsonDepartment, allocator);
    }

    //return
    return jsonDepartments;

}
