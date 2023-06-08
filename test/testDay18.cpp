#include "cppunit/TestCase.h"
#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

#include "day18.hpp"
#include "logger.hpp"

class TestDay18 : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDay18);
    CPPUNIT_TEST(testBasicMath);
    CPPUNIT_TEST(testAdvancedMath);
    CPPUNIT_TEST(inputFile);
    CPPUNIT_TEST_SUITE_END();

public:
    void testBasicMath(void);
    void testAdvancedMath(void);
    void inputFile(void);

private:
    std::string operation1 = "1 + 2 * 3 + 4 * 5 + 6";
    std::string operation2 = "1 + (2 * 3) + (4 * (5 + 6))";
    std::string operation3 = "2 * 3 + (4 * 5)";
    std::string operation4 = "5 + (8 * 3 + 9 + 3 * 4 * 3)";
    std::string operation5 = "5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))";
    std::string operation6 = "((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2";
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestDay18);

void TestDay18::testBasicMath(void)
{
    CPPUNIT_ASSERT_EQUAL(
        static_cast<int64_t>(71),
        std::stol(day18::compute(operation1, day18::Math::Basic)));
    CPPUNIT_ASSERT_EQUAL(
        static_cast<int64_t>(51),
        std::stol(day18::compute(operation2, day18::Math::Basic)));
    CPPUNIT_ASSERT_EQUAL(
        static_cast<int64_t>(26),
        std::stol(day18::compute(operation3, day18::Math::Basic)));
    CPPUNIT_ASSERT_EQUAL(
        static_cast<int64_t>(437),
        std::stol(day18::compute(operation4, day18::Math::Basic)));
    CPPUNIT_ASSERT_EQUAL(
        static_cast<int64_t>(12240),
        std::stol(day18::compute(operation5, day18::Math::Basic)));
    CPPUNIT_ASSERT_EQUAL(
        static_cast<int64_t>(13632),
        std::stol(day18::compute(operation6, day18::Math::Basic)));
}

void TestDay18::testAdvancedMath(void)
{
    CPPUNIT_ASSERT_EQUAL(
        static_cast<int64_t>(231),
        std::stol(day18::compute(operation1, day18::Math::Advanced)));
    CPPUNIT_ASSERT_EQUAL(
        static_cast<int64_t>(51),
        std::stol(day18::compute(operation2, day18::Math::Advanced)));
    CPPUNIT_ASSERT_EQUAL(
        static_cast<int64_t>(46),
        std::stol(day18::compute(operation3, day18::Math::Advanced)));
    CPPUNIT_ASSERT_EQUAL(
        static_cast<int64_t>(1445),
        std::stol(day18::compute(operation4, day18::Math::Advanced)));
    CPPUNIT_ASSERT_EQUAL(
        static_cast<int64_t>(669060),
        std::stol(day18::compute(operation5, day18::Math::Advanced)));
    CPPUNIT_ASSERT_EQUAL(
        static_cast<int64_t>(23340),
        std::stol(day18::compute(operation6, day18::Math::Advanced)));
}

void TestDay18::inputFile(void)
{
    const std::string filename = "input/day18.txt";
    int64_t result1, result2;
    CPPUNIT_ASSERT_EQUAL(Ok, day18::execute(filename, result1, result2));
    CPPUNIT_ASSERT_EQUAL(static_cast<int64_t>(11297104473091), result1);
    CPPUNIT_ASSERT_EQUAL(static_cast<int64_t>(185348874183674), result2);
}