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

		/*TEST_METHOD(TestAddTempStudents)
		{
            ///config
		    Department dpt;
            dpt.m_tempStudents.clear();
            Student xiaoming, xiaohong;
            dpt.m_tempStudents.push_back(&xiaoming);
            dpt.m_tempStudents.push_back(&xiaohong);
            ///test
            Assert::AreEqual(2, (int)dpt.m_tempStudents.size());
		}

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