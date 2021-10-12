#include "cppunit/TestCase.h"
#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

#include "day11.hpp"
#include "logger.hpp"

class TestDay11 : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDay11);
    CPPUNIT_TEST(testFile);
    CPPUNIT_TEST(inputFile);
    CPPUNIT_TEST_SUITE_END();

public:
    void testFile(void);
    void inputFile(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestDay11);

void TestDay11::testFile(void)
{
    Logger::setSilentMode(true);
    std::string filename = "input/day11_test.txt";
    unsigned int result1, result2;
    if (Day11::execute(filename, result1, result2) != Ok)
    {
        CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT_EQUAL(37U, result1);
    CPPUNIT_ASSERT_EQUAL(26U, result2);
}

void TestDay11::inputFile(void)
{
    Logger::setSilentMode(true);
    std::string filename = "input/day11.txt";
    unsigned int result1, result2;
    if (Day11::execute(filename, result1, result2) != Ok)
    {
        CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT_EQUAL(2281U, result1);
    CPPUNIT_ASSERT_EQUAL(2085U, result2);
}