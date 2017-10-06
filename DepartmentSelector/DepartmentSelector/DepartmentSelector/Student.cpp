#include "stdafx.h"
#include "Student.h"


Student::Student(std::string id)
{
    this->m_id = id;
}

std::string Student::GetId()
{
    return m_id;
}

Student::~Student()
{
}
