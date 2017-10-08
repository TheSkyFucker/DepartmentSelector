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
             Assert::AreEqual(ID_YAOYAO, yaoyao.Id());
             Assert::AreEqual(ID_PAOPAO, paopao.Id());
        }

        TEST_METHOD(AddFreeTimeTest)
        {
            //config
            const TimeSegment FREE_TIME_1("Sat.14: 00~16: 00");
            const TimeSegment FREE_TIME_2("Sat.17: 00~18: 00");

            //test
            Student yaoyao("031502522");
            yaoyao.AddFreeTime(FREE_TIME_1);
            yaoyao.AddFreeTime(FREE_TIME_2);
            Assert::AreEqual(2, (int)yaoyao.FreeTimes().size());
        }
    };
}