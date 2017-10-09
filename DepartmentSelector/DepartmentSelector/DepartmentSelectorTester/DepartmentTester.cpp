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
            Student paopao("031502442");
            Student yaoyao("031502522");
            //test
            dpt.AddTempStudent(&paopao);
            dpt.AddTempStudent(&yaoyao);
            Assert::AreEqual(2, (int)dpt.TempStudents().size());
		}

        TEST_METHOD(AddSchedule)
        {
            //config
            const TimeSegment SCHEDULE_1("Sat.14: 00~16: 00");
            const TimeSegment SCHEDULE_2("Sat.15: 00~18: 00");
            
            //test
            Department dpt("D0001");
            dpt.AddSchedule(SCHEDULE_1);
            dpt.AddSchedule(SCHEDULE_2);
            Assert::AreEqual(1, (int)dpt.Schedules().size());
            Assert::AreEqual(14 * 60, dpt.Schedules().back().Begin());
            Assert::AreEqual(18 * 60, dpt.Schedules().back().End());
        }

        TEST_METHOD(DeleteConflictStudents)
        {
            //config
            const TimeSegment PAOPAO_FREE_TIME("Sat.14: 00~16: 00");
            const TimeSegment YAOYAO_FREE_TIME("Sat.16: 00~18: 00");
            const TimeSegment SCHEDULE("Sat.16: 00~17: 00");
            Student paopao("031502442");
            Student yaoyao("031502522");
            paopao.AddFreeTime(PAOPAO_FREE_TIME);
            yaoyao.AddFreeTime(YAOYAO_FREE_TIME);
            Department dpt("D23333");
            dpt.AddSchedule(SCHEDULE);
            dpt.AddTempStudent(&paopao);
            dpt.AddTempStudent(&yaoyao);

            //test
            dpt.DeleteConflictStudents();
            Assert::AreEqual(1, (int)dpt.TempStudents().size());
            Assert::AreEqual((int)(&yaoyao), (int)dpt.TempStudents().back());;
        }

        TEST_METHOD(SelectStudents_Logic1)
        {
            //config
            const TimeSegment PAOPAO_FREE_TIME("Sat.14: 00~16: 00");
            const TimeSegment YAOYAO_FREE_TIME("Sat.16: 00~18: 00");
            const TimeSegment SCHEDULE("Sat.16: 00~17: 00");
            Student paopao("031502442");
            Student yaoyao("031502522");
            paopao.AddFreeTime(PAOPAO_FREE_TIME);
            yaoyao.AddFreeTime(YAOYAO_FREE_TIME);
            Department dpt("D23333");
            dpt.AddSchedule(SCHEDULE);
            dpt.AddTempStudent(&paopao);
            dpt.AddTempStudent(&yaoyao);

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
            paopao.AddTag("aaa");
            Department dpt("D1212");
            dpt.AddTag("aaa");
            dpt.AddTag("aaaa");
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
            paopao.AddTag("aaa");
            paopao.AddTag("bbb");
            paopao.AddDepartment("D23333");
            paopao.AddDepartment("D24444");
            paopao.AddDepartment("D25555");

            Student yaoyao("03152522");
            yaoyao.AddTag("aaa");
            yaoyao.AddTag("ccc");

            Student hbb("?????????");
            hbb.AddTag("aaa");
            hbb.AddTag("bbb");
            hbb.AddDepartment("D23333");
            paopao.AddDepartment("D25555");

            //config department
            Department dpt("D1212");
            dpt.AddTag("aaa");
            dpt.AddTag("bbb");

            //test
            dpt.AddTempStudent(&yaoyao);
            dpt.AddTempStudent(&hbb);
            dpt.AddTempStudent(&paopao);
            dpt.SortTempStudents();
            std::vector<Student *> temp = dpt.TempStudents();
            Assert::AreEqual(paopao.Id(), temp[0]->Id());
            Assert::AreEqual(hbb.Id(), temp[1]->Id());
            Assert::AreEqual(yaoyao.Id(), temp[2]->Id());

        }

        TEST_METHOD(SelectStudents_Logic2)
        {
            //config students
            Student paopao("031502442");
            paopao.AddTag("aaa");
            paopao.AddTag("bbb");
            paopao.AddDepartment("D23333");
            paopao.AddDepartment("D24444");
            paopao.AddDepartment("D25555");

            Student yaoyao("031502522");
            yaoyao.AddTag("aaa");
            yaoyao.AddTag("ccc");

            Student hbb("?????????");
            hbb.AddTag("aaa");
            hbb.AddTag("bbb");
            hbb.AddDepartment("D23333");

            //config department
            Department dpt("D1212");
            dpt.AddTag("aaa");
            dpt.AddTag("bbb");
            dpt.AddTempStudent(&paopao);
            dpt.AddTempStudent(&yaoyao);
            dpt.AddTempStudent(&hbb);

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

        TEST_METHOD(AddStudent)
        {
            //config
            Student paopao("031502442");
            Student yaoyao("031502522");
            Department dpt1("D0001");
            Department dpt2("D0002");

            //test
            try
            {
                dpt1.SetMemberLimit(10);
                dpt1.AddTempStudent(&paopao);
                dpt1.AddTempStudent(&yaoyao);
                dpt1.SelectStudents();
            }
            catch (std::exception e)
            {
                Assert::IsTrue(false);
            }
            Assert::AreEqual(1, (int)paopao.Departments().size());
            Assert::AreEqual(dpt1.Id(), paopao.Departments().back());
        }


	};
}