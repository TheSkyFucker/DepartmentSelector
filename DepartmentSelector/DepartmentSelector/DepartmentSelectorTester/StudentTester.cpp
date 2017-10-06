#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DepartmentSelector/Student.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StudentTester
{
    TEST_CLASS(StudentTester)
    {
    public:

         TEST_METHOD(ConstructTest)
        {
             //config
             const std::string ID_YAOYAO = "031502522";
             const std::string ID_PAOPAO = "031502442";
             Student yaoyao(ID_YAOYAO);
             Student paopao(ID_PAOPAO);
             Assert::AreEqual(ID_YAOYAO, yaoyao.GetId());
             Assert::AreEqual(ID_PAOPAO, paopao.GetId());
        }
    };
}