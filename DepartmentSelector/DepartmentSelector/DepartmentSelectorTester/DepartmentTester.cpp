#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DepartmentSelector/Department.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DepartmentTester
{		
	TEST_CLASS(DepartmentTester)
	{
	public:

        TEST_METHOD(ConstructTest)
        {
            //config
            const std::string ID_DEPARTMENT_1 = "031502522";
            const std::string ID_DEPARTMENT_2 = "031502442";
            Department dpt1(ID_DEPARTMENT_1);
            Department dpt2(ID_DEPARTMENT_2);
            Assert::AreEqual(ID_DEPARTMENT_1, dpt1.GetId());
            Assert::AreEqual(ID_DEPARTMENT_2, dpt2.GetId());
        }

		TEST_METHOD(AddTempStudentsTest)
		{
            ///config
		    Department dpt("D0001");
            dpt.m_tempStudents.clear();
            Student paopao("031502442");
            Student yaoyao("031502522");
            //test
            dpt.m_tempStudents.push_back(&paopao);
            dpt.m_tempStudents.push_back(&yaoyao);
            Assert::AreEqual(2, (int)dpt.m_tempStudents.size());
		}

        TEST_METHOD(AddScheduleTest)
        {
            //config
            const TimeSegment SCHEDULE_1("Sat.14: 00~16: 00");
            const TimeSegment SCHEDULE_2("Sat.14: 00~16: 00");

            //test
            Department dpt("D0001");
            dpt.m_schedules.push_back(SCHEDULE_1);
            dpt.m_schedules.push_back(SCHEDULE_2);
            Assert::AreEqual(2, (int)dpt.m_schedules.size());
        }


	};
}