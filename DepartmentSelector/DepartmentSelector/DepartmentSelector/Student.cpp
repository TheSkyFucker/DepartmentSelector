#include "stdafx.h"
#include "Student.h"


Student::Student(std::string id) throw()
{
    this->m_id = id;
}

std::string Student::Id() const throw()
{
    return m_id;
}

Student::~Student()
{
}
