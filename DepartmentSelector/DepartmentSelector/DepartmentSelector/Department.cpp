#include "stdafx.h"
#include "Department.h"


Department::Department(std::string id)
{
    m_id = id;
}

std::string Department::GetId()
{
    return m_id;
}

Department::~Department()
{
}