#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DepartmentSelector/TimeSegment.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TimeSegmentTester
{
    TEST_CLASS(TimeSegmentTester)
    {
    public:

        TEST_METHOD(ConstructTest)
        {
            //config
            const std::string TIME_SEGMENT_1 = "Mon.16: 00~18: 00";
            const int TIME_SEGMENT_DAY = 1;
            const int TIME_SEGMENT_BEGIN = 16 * 60;
            const int TIME_SEGMENT_END = 18 * 60;
            TimeSegment seg(TIME_SEGMENT_1);

            //test
            Assert::AreEqual(TIME_SEGMENT_DAY, seg.Day());
            Assert::AreEqual(TIME_SEGMENT_BEGIN, seg.Begin());
            Assert::AreEqual(TIME_SEGMENT_END, seg.End());
        }

        TEST_METHOD(ConflictTest)
        {
            //config
            const std::string TEST_TIME_SEGMENT_1 = "Mon.16: 00~18: 00";
            const std::string TEST_TIME_SEGMENT_2 = "Mon.13: 00~19: 00";
            const std::string TEST_TIME_SEGMENT_3 = "Sun.13: 00~19: 00";
            const std::string TEST_TIME_SEGMENT_4 = "Mon.11: 00~12: 00";
            TimeSegment seg1(TEST_TIME_SEGMENT_1);
            TimeSegment seg2(TEST_TIME_SEGMENT_2);
            TimeSegment seg3(TEST_TIME_SEGMENT_3);
            TimeSegment seg4(TEST_TIME_SEGMENT_4);

            //test
            Assert::IsFalse(seg1.Include(seg2));
            Assert::IsTrue(seg2.Include(seg1));
            Assert::IsFalse(seg1.Include(seg4));
            Assert::IsFalse(seg3.Include(seg4));

        }

        TEST_METHOD(Combine)
        {
            //config
            const std::string TEST_TIME_SEGMENT_1 = "Mon.16: 00~18: 00";
            const std::string TEST_TIME_SEGMENT_2 = "Mon.17: 00~20: 00";
            const std::string TEST_TIME_SEGMENT_3 = "Mon.17: 00~17: 30";
            const std::string TEST_TIME_SEGMENT_4 = "ddd.17: 00~17: 30";
            TimeSegment seg1(TEST_TIME_SEGMENT_1);
            TimeSegment seg2(TEST_TIME_SEGMENT_2);
            TimeSegment seg3(TEST_TIME_SEGMENT_3);
            TimeSegment seg4(TEST_TIME_SEGMENT_4);

            //test
            Assert::IsTrue(seg1.Combine(seg2));
            Assert::IsTrue(seg1.Combine(seg3));
            Assert::IsFalse(seg1.Combine(seg4));
            Assert::IsTrue(seg2.Combine(seg3));

        }

        TEST_METHOD(Cut)
        {
            //config
            const std::string TEST_TIME_SEGMENT_1 = "Mon.16: 00~18: 00";
            const std::string TEST_TIME_SEGMENT_2 = "Mon.17: 00~20: 00";
            const std::string TEST_TIME_SEGMENT_3 = "Mon.17: 30~17: 40";
            const std::string TEST_TIME_SEGMENT_4 = "Mon.13: 30~13: 40";
            TimeSegment seg1(TEST_TIME_SEGMENT_1);
            TimeSegment seg2(TEST_TIME_SEGMENT_2);
            TimeSegment seg3(TEST_TIME_SEGMENT_3);
            TimeSegment seg4(TEST_TIME_SEGMENT_4);

            //test
            auto segs1 = seg1.Cut(seg2);
            Assert::AreEqual(1, (int)segs1.size());
            Assert::AreEqual(16 * 60, segs1.back().Begin());
            Assert::AreEqual(17 * 60, segs1.back().End());
            seg2.Cut(seg3);
            auto segs2 = seg2.Cut(seg3);
            Assert::AreEqual(2, (int)segs2.size());
            Assert::AreEqual(17 * 60, segs2[0].Begin());
            Assert::AreEqual(17 * 60 + 30, segs2[0].End());
            Assert::AreEqual(17 * 60 + 40, segs2[1].Begin());
            Assert::AreEqual(20 * 60, segs2[1].End());
            auto segs3 = seg1.Cut(seg4);
            Assert::AreEqual(1, (int)segs3.size());
        }

    };
}