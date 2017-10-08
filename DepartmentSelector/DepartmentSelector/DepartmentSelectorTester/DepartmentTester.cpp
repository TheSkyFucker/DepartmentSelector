#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DepartmentSelector/Department.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DepartmentTester
{		
	TEST_CLASS(DepartmentTester)
	{

    bool ExistStudent(const Student * student, const std::vector<Student *> &students) const
    {
        for (auto aStudent : students)
        {
            if (student == aStudent)
            {
                return true;
            }
        }
        return false;
    }

	public:

        TEST_METHOD(Construct)
        {
            //config
            const std::string ID_DEPARTMENT_1 = "031502522";
            const std::string ID_DEPARTMENT_2 = "031502442";
            Department dpt1(ID_DEPARTMENT_1);
            Department dpt2(ID_DEPARTMENT_2);
            Assert::AreEqual(ID_DEPARTMENT_1, dpt1.Id());
            Assert::AreEqual(ID_DEPARTMENT_2, dpt2.Id());
        }

		TEST_METHOD(AddTempStudents)
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

        TEST_METHOD(AddSchedule)
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

        TEST_METHOD(DeleteConflictStudents)
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

        TEST_METHOD(SelectStudents_Logic1)
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

            //test only freetime conflict
            dpt.SetMemberLimit(10);
            try
            {
                dpt.SelectStudents();
            }
            catch (std::exception e)
            {
                Assert::IsTrue(false);
            }
            std::vector<Student *> students = dpt.Students();
            ExistStudent(&paopao, students);


        }

        TEST_METHOD(SetMemberLimit)
        {
            //config
            Department dpt("D0001");
            
            //test < 0
            bool cat = false;
            try
            {
                dpt.SetMemberLimit(-1);
            }
            catch (std::exception e)
            {
                cat = true;
            }
            Assert::IsTrue(cat);

            //test >= 0
            cat = false;
            try
            {
                dpt.SetMemberLimit(100);
            }
            catch (std::exception e)
            {
                cat = true;
            }
            Assert::IsFalse(cat);
        }

        TEST_METHOD(GetStudentValue)
        {
            //config
            Student paopao("031502442");
            paopao.m_tags.push_back("aaa");
            Department dpt("D1212");
            dpt.m_tags.push_back("aaa");
            dpt.m_tags.push_back("aaaa");
            const double PAOPAO_VALUE = 1. * 1 / (1 + 0);
            const double EPS = 1e-6;
            
            //test
            double val = dpt.GetStudentValue(paopao);
            Assert::IsTrue(fabs(val - PAOPAO_VALUE) < EPS);

        }

        TEST_METHOD(SortTempStudents)
        {

            //config students
            Student paopao("031502442");
            paopao.m_tags.push_back("aaa");
            paopao.m_tags.push_back("bbb");
            paopao.m_departments.push_back("D23333");
            paopao.m_departments.push_back("D24444");
            paopao.m_departments.push_back("D25555");

            Student yaoyao("031502442");
            yaoyao.m_tags.push_back("aaa");
            yaoyao.m_tags.push_back("ccc");

            Student hbb("?????????");
            hbb.m_tags.push_back("aaa");
            hbb.m_tags.push_back("bbb");
            hbb.m_departments.push_back("D23333");

            //config department
            Department dpt("D1212");
            dpt.m_tags.push_back("aaa");
            dpt.m_tags.push_back("bbb");

            //test
            dpt.m_tempStudents.push_back(&yaoyao);
            dpt.m_tempStudents.push_back(&hbb);
            dpt.m_tempStudents.push_back(&paopao);
            dpt.SortTempStudents();
            Assert::AreEqual(yaoyao.Id(), dpt.m_tempStudents[0]->Id());
            Assert::AreEqual(hbb.Id(), dpt.m_tempStudents[1]->Id());
            Assert::AreEqual(paopao.Id(), dpt.m_tempStudents[2]->Id());

        }

        TEST_METHOD(SelectStudents_Logic2)
        {
            //config students
            Student paopao("031502442");
            paopao.m_tags.push_back("aaa");
            paopao.m_tags.push_back("bbb");
            paopao.m_departments.push_back("D23333");
            paopao.m_departments.push_back("D24444");
            paopao.m_departments.push_back("D25555");

            Student yaoyao("031502442");
            yaoyao.m_tags.push_back("aaa");
            yaoyao.m_tags.push_back("ccc");

            Student hbb("?????????");
            hbb.m_tags.push_back("aaa");
            hbb.m_tags.push_back("bbb");
            hbb.m_departments.push_back("D23333");

            //config department
            Department dpt("D1212");
            dpt.m_tags.push_back("aaa");
            dpt.m_tags.push_back("bbb");
            dpt.m_tempStudents.push_back(&paopao);
            dpt.m_tempStudents.push_back(&yaoyao);
            dpt.m_tempStudents.push_back(&hbb);

            //test
            dpt.SetMemberLimit(2);
            try
            {
                dpt.SelectStudents();
            }
            catch (std::exception e)
            {
                Assert::IsFalse(true);  //unexpected
            }
            Assert::AreEqual(2, (int)dpt.Students().size());
            Assert::AreEqual(yaoyao.Id(), dpt.Students()[0]->Id());
            Assert::AreEqual(hbb.Id(), dpt.Students()[1]->Id());
        }


	};
}