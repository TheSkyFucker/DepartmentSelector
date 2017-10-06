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

        /*

        TEST_METHOD(TestSchedulesConflict)
		{
            ///config
            Department dpt;
            std::vector<std::string> freeTimes;
            //TODO: set freeTimes

            //test
            Assert::IsFalse(dpt.IsSchedulesConflict(freeTimes));

            //TODO: more test
		}

        TEST_METHOD(TestDeleteConflictStudents)
		{
            ///config
            //Department dpt;
            
		}*/

	};
}