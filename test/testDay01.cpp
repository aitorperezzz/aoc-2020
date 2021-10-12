#include "cppunit/TestCase.h"
#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

#include "day01.hpp"
#include "logger.hpp"

class TestDay01 : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDay01);
    CPPUNIT_TEST(testFile);
    CPPUNIT_TEST(inputFile);
    CPPUNIT_TEST_SUITE_END();

public:
    void testFile(void);
    void inputFile(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestDay01);

void TestDay01::testFile(void)
{
    Logger::setSilentMode(true);

    std::string filename = "input/day01_test.txt";
    int result;
    if (Day01::executePartOne(filename, result) != Ok)
    {
        CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT_EQUAL(514579, result);

    if (Day01::executePartTwo(filename, result) != Ok)
    {
        CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT_EQUAL(241861950, result);
}

void TestDay01::inputFile(void)
{
    Logger::setSilentMode(true);

    std::string filename = "input/day01.txt";
    int result;
    if (Day01::executePartOne(filename, result) != Ok)
    {
        CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT_EQUAL(482811, result);

    if (Day01::executePartTwo(filename, result) != Ok)
    {
        CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT_EQUAL(193171814, result);
}