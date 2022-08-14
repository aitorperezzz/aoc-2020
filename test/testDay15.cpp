#include "cppunit/TestCase.h"
#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

#include "day15.hpp"
#include "logger.hpp"

class TestDay15 : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDay15);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();

public:
    void test(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestDay15);

void TestDay15::test(void)
{
    Logger::setSilentMode(true);
    std::vector<int> numbers;
    int iterations;
    int result;

    iterations = 2020;

    numbers = {1, 3, 2};
    CPPUNIT_ASSERT_EQUAL(Ok, day15::execute(numbers, iterations, result));
    CPPUNIT_ASSERT_EQUAL(1, result);

    numbers = {2, 1, 3};
    CPPUNIT_ASSERT_EQUAL(Ok, day15::execute(numbers, iterations, result));
    CPPUNIT_ASSERT_EQUAL(10, result);

    numbers = {1, 2, 3};
    CPPUNIT_ASSERT_EQUAL(Ok, day15::execute(numbers, iterations, result));
    CPPUNIT_ASSERT_EQUAL(27, result);

    numbers = {2, 3, 1};
    CPPUNIT_ASSERT_EQUAL(Ok, day15::execute(numbers, iterations, result));
    CPPUNIT_ASSERT_EQUAL(78, result);

    numbers = {3, 2, 1};
    CPPUNIT_ASSERT_EQUAL(Ok, day15::execute(numbers, iterations, result));
    CPPUNIT_ASSERT_EQUAL(438, result);

    numbers = {3, 1, 2};
    CPPUNIT_ASSERT_EQUAL(Ok, day15::execute(numbers, iterations, result));
    CPPUNIT_ASSERT_EQUAL(1836, result);

    numbers = {14, 8, 16, 0, 1, 17};
    CPPUNIT_ASSERT_EQUAL(Ok, day15::execute(numbers, iterations, result));
    CPPUNIT_ASSERT_EQUAL(240, result);

    iterations = 30000000;

    numbers = {0, 3, 6};
    CPPUNIT_ASSERT_EQUAL(Ok, day15::execute(numbers, iterations, result));
    CPPUNIT_ASSERT_EQUAL(175594, result);

    numbers = {1, 3, 2};
    CPPUNIT_ASSERT_EQUAL(Ok, day15::execute(numbers, iterations, result));
    CPPUNIT_ASSERT_EQUAL(2578, result);

    numbers = {2, 1, 3};
    CPPUNIT_ASSERT_EQUAL(Ok, day15::execute(numbers, iterations, result));
    CPPUNIT_ASSERT_EQUAL(3544142, result);

    numbers = {1, 2, 3};
    CPPUNIT_ASSERT_EQUAL(Ok, day15::execute(numbers, iterations, result));
    CPPUNIT_ASSERT_EQUAL(261214, result);

    numbers = {2, 3, 1};
    CPPUNIT_ASSERT_EQUAL(Ok, day15::execute(numbers, iterations, result));
    CPPUNIT_ASSERT_EQUAL(6895259, result);

    numbers = {3, 2, 1};
    CPPUNIT_ASSERT_EQUAL(Ok, day15::execute(numbers, iterations, result));
    CPPUNIT_ASSERT_EQUAL(18, result);

    numbers = {3, 1, 2};
    CPPUNIT_ASSERT_EQUAL(Ok, day15::execute(numbers, iterations, result));
    CPPUNIT_ASSERT_EQUAL(362, result);

    numbers = {14, 8, 16, 0, 1, 17};
    CPPUNIT_ASSERT_EQUAL(Ok, day15::execute(numbers, iterations, result));
    CPPUNIT_ASSERT_EQUAL(505, result);
}