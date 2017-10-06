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

        TEST_METHOD(DeleteConflictStudentsTest)
        {
            //config
            const TimeSegment PAOPAO_FREE_TIME("Sat.14: 00~16: 00");
            const TimeSegment YAOYAO_FREE_TIME("Sat.16: 00~18: 00");
            const TimeSegment SCHEDULE("Sat.16: 00~17: 00");
            Student paopao("031502442");
            Student yaoyao("031502522");
            paopao.m_freeTimes.push_back(PAOPAO_FREE_TIME);
            yaoyao.m_freeTimes.push_back(YAOYAO_FREE_TIME);
            Department dpt("D23333");
            dpt.m_schedules.push_back(SCHEDULE);
            dpt.m_tempStudents.push_back(&paopao);
            dpt.m_tempStudents.push_back(&yaoyao);

            //test
            dpt.DeleteConflictStudents();
            Assert::AreEqual(1, (int)dpt.m_tempStudents.size());
            Assert::AreEqual((int)(&yaoyao), (int)dpt.m_tempStudents.back());;
        }


	};
}