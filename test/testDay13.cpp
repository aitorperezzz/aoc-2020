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
    CPPUNIT_TEST(chineseTheorem);
    CPPUNIT_TEST(solveSecondPart);
    CPPUNIT_TEST_SUITE_END();

public:
    void testFile(void);
    void inputFile(void);
    void chineseTheorem(void);
    void solveSecondPart(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestDay13);

void TestDay13::testFile(void)
{
    Logger::setSilentMode(true);
    std::string filename = "input/day13_test.txt";
    int result1;
    int64_t result2;
    if (day13::execute(filename, result1, result2) != Ok)
    {
        CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT_EQUAL(295, result1);
    CPPUNIT_ASSERT_EQUAL(static_cast<int64_t>(1068781), result2);
}

void TestDay13::inputFile(void)
{
    Logger::setSilentMode(true);
    std::string filename = "input/day13.txt";
    int result1;
    int64_t result2;
    if (day13::execute(filename, result1, result2) != Ok)
    {
        CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT_EQUAL(246, result1);
    CPPUNIT_ASSERT_EQUAL(static_cast<int64_t>(939490236001473), result2);
}

void TestDay13::chineseTheorem(void)
{
    Logger::setSilentMode(true);
    std::vector<int64_t> results;
    std::vector<int64_t> divisors;

    // Chain 67,7,59,61
    results = {0, -1, -2, -3};
    divisors = {67, 7, 59, 61};
    CPPUNIT_ASSERT_EQUAL(static_cast<int64_t>(754018),
                         day13::solveChineseTheorem(results, divisors));

    // Chain 1789,37,47,1889
    results = {0, -1, -2, -3};
    divisors = {1789, 37, 47, 1889};
    CPPUNIT_ASSERT_EQUAL(static_cast<int64_t>(1202161486),
                         day13::solveChineseTheorem(results, divisors));
}

void TestDay13::solveSecondPart(void)
{
    Logger::setSilentMode(true);
    std::vector<int> busIds;

    // Chain 67,7,59,61
    busIds = {67, 7, 59, 61};
    CPPUNIT_ASSERT_EQUAL(static_cast<int64_t>(754018),
                         day13::solvePartTwo(busIds));

    // Chain 1789,37,47,1889
    busIds = {1789, 37, 47, 1889};
    CPPUNIT_ASSERT_EQUAL(static_cast<int64_t>(1202161486),
                         day13::solvePartTwo(busIds));

    // Chain 17,x,13,19
    busIds = {17, -1, 13, 19};
    CPPUNIT_ASSERT_EQUAL(static_cast<int64_t>(3417),
                         day13::solvePartTwo(busIds));

    // Chain 67,x,7,59,61
    busIds = {67, -1, 7, 59, 61};
    CPPUNIT_ASSERT_EQUAL(static_cast<int64_t>(779210),
                         day13::solvePartTwo(busIds));

    // Chain 67,7,x,59,61
    busIds = {67, 7, -1, 59, 61};
    CPPUNIT_ASSERT_EQUAL(static_cast<int64_t>(1261476),
                         day13::solvePartTwo(busIds));

    // Chain 7,13,x,x,59,x,31,19
    busIds = {7, 13, -1, -1, 59, -1, 31, 19};
    CPPUNIT_ASSERT_EQUAL(static_cast<int64_t>(1068781),
                         day13::solvePartTwo(busIds));
}