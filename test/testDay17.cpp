#include "cppunit/TestCase.h"
#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

#include "day17.hpp"
#include "logger.hpp"

class TestDay17 : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDay17);
    CPPUNIT_TEST(testFile);
    CPPUNIT_TEST(inputFile);
    CPPUNIT_TEST_SUITE_END();

public:
    void testFile(void);
    void inputFile(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestDay17);

void TestDay17::testFile(void)
{
    const std::string filename = "input/day17_test.txt";
    size_t result1, result2;
    CPPUNIT_ASSERT_EQUAL(Ok, day17::execute(filename, result1, result2));
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(112), result1);
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(848), result2);
}

void TestDay17::inputFile(void)
{
    const std::string filename = "input/day17.txt";
    size_t result1, result2;
    CPPUNIT_ASSERT_EQUAL(Ok, day17::execute(filename, result1, result2));
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(346), result1);
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1632), result2);
}
