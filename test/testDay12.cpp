#include "cppunit/TestCase.h"
#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

#include "day12.hpp"
#include "logger.hpp"

class TestDay12 : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDay12);
    CPPUNIT_TEST(testFile);
    CPPUNIT_TEST(inputFile);
    CPPUNIT_TEST_SUITE_END();

public:
    void testFile(void);
    void inputFile(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestDay12);

void TestDay12::testFile(void)
{
    Logger::setSilentMode(true);
    std::string filename = "input/day12_test.txt";
    uint32_t result;
    if (day12::execute(filename, result) != Ok)
    {
        CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT_EQUAL(25U, result);
}

void TestDay12::inputFile(void)
{
    Logger::setSilentMode(true);
    std::string filename = "input/day12.txt";
    uint32_t result;
    if (day12::execute(filename, result) != Ok)
    {
        CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT_EQUAL(1294U, result);
}