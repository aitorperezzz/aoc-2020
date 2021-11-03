#include "cppunit/TestCase.h"
#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

#include "day13.hpp"
#include "logger.hpp"

class TestDay13 : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDay13);
    CPPUNIT_TEST(testFile);
    CPPUNIT_TEST(inputFile);
    CPPUNIT_TEST_SUITE_END();

public:
    void testFile(void);
    void inputFile(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestDay13);

void TestDay13::testFile(void)
{
    Logger::setSilentMode(true);
    std::string filename = "input/day13_test.txt";
    int result;
    if (day13::execute(filename, result) != Ok)
    {
        CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT_EQUAL(295, result);
}

void TestDay13::inputFile(void)
{
    Logger::setSilentMode(true);
    std::string filename = "input/day13.txt";
    int result;
    if (day13::execute(filename, result) != Ok)
    {
        CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT_EQUAL(246, result);
}