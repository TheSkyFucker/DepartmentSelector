#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DepartmentSelector/Student.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StudentTester
{
    TEST_CLASS(StudentTester)
    {
    public:

        TEST_METHOD(Id)
        {
             //config
             const std::string ID_YAOYAO = "031502522";
             const std::string ID_PAOPAO = "031502442";
             Student yaoyao(ID_YAOYAO);
             Student paopao(ID_PAOPAO);
             Assert::AreEqual(ID_YAOYAO, yaoyao.Id());
             Assert::AreEqual(ID_PAOPAO, paopao.Id());
        }

        TEST_METHOD(AddFreeTime)
        {
            //config
            const TimeSegment FREE_TIME_1("Sat.14: 00~16: 00");
            const TimeSegment FREE_TIME_2("Sat.17: 00~18: 00");
            const TimeSegment FREE_TIME_3("Sat.16: 00~17: 00");

            //test
            Student yaoyao("031502522");
            yaoyao.AddFreeTime(FREE_TIME_1);
            yaoyao.AddFreeTime(FREE_TIME_2);
            Assert::AreEqual(2, (int)yaoyao.FreeTimes().size());
            yaoyao.AddFreeTime(FREE_TIME_3);
            Assert::AreEqual(1, (int)yaoyao.FreeTimes().size());
            Assert::AreEqual(14 * 60, yaoyao.FreeTimes().back().Begin());
            Assert::AreEqual(18 * 60, yaoyao.FreeTimes().back().End());
        }

        TEST_METHOD(AddTag)
        {
            //config
            const std::string TAG_1 = "tag0001";
            const std::string TAG_2 = "tag0002";
            Student yaoyao("031502522");
            yaoyao.AddTag(TAG_1);
            yaoyao.AddTag(TAG_2);

            //test
            auto tags = yaoyao.Tags();
            Assert::AreEqual(2, (int)tags.size());
            Assert::AreEqual(TAG_1, tags[0]);
            Assert::AreEqual(TAG_2, tags[1]);
        }

        TEST_METHOD(AddDepartment)
        {
            //config
            const std::string DEPARTMENT_1 = "D0001";
            const std::string DEPARTMENT_2 = "D0002";
            Student yaoyao("031502522");
            yaoyao.AddDepartment(DEPARTMENT_1);
            yaoyao.AddDepartment(DEPARTMENT_2);

            //test
            auto departments = yaoyao.Departments();
            Assert::AreEqual(2, (int)departments.size());
            Assert::AreEqual(DEPARTMENT_1, departments[0]);
            Assert::AreEqual(DEPARTMENT_2, departments[1]);
            yaoyao.AddDepartment(DEPARTMENT_1);
            Assert::AreEqual(2, (int)departments.size());
        }

        TEST_METHOD(AddApplication)
        {
            //config
            const std::string APPLICATION_1 = "D0001";
            const std::string APPLICATION_2 = "D0002";
            Student yaoyao("031502522");
            yaoyao.AddApplication(APPLICATION_1);
            yaoyao.AddApplication(APPLICATION_2);

            //test
            auto applications = yaoyao.Applications();
            Assert::AreEqual(2, (int)applications.size());
            Assert::AreEqual(APPLICATION_1, applications[0]);
            Assert::AreEqual(APPLICATION_2, applications[1]);
            yaoyao.AddApplication(APPLICATION_1);
            applications = yaoyao.Applications();
            Assert::AreEqual(3, (int)applications.size());
        }

    };
}