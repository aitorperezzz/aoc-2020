#include "cppunit/TestCase.h"
#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

#include "day14.hpp"
#include "logger.hpp"

class TestDay14 : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDay14);
    CPPUNIT_TEST(testFile);
    CPPUNIT_TEST(inputFile);
    CPPUNIT_TEST_SUITE_END();

public:
    void testFile(void);
    void inputFile(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestDay14);

void TestDay14::testFile(void)
{
    unsigned long result;
    std::string filename;

    filename = "input/day14_test.txt";
    CPPUNIT_ASSERT_EQUAL(Ok,
                         day14::execute(filename, day14::Version::ONE, result));
    CPPUNIT_ASSERT_EQUAL(static_cast<unsigned long>(165), result);

    filename = "input/day14_test2.txt";
    CPPUNIT_ASSERT_EQUAL(Ok,
                         day14::execute(filename, day14::Version::TWO, result));
    CPPUNIT_ASSERT_EQUAL(static_cast<unsigned long>(208), result);
}

void TestDay14::inputFile(void)
{
    std::string filename = "input/day14.txt";
    unsigned long result;

    // Test version 1 of the program
    CPPUNIT_ASSERT_EQUAL(Ok,
                         day14::execute(filename, day14::Version::ONE, result));
    CPPUNIT_ASSERT_EQUAL(static_cast<unsigned long>(11501064782628), result);

    // Test version 2 of the program
    CPPUNIT_ASSERT_EQUAL(Ok,
                         day14::execute(filename, day14::Version::TWO, result));
    CPPUNIT_ASSERT_EQUAL(static_cast<unsigned long>(5142195937660), result);
}