#include "cppunit/TestCase.h"
#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

#include "day16.hpp"
#include "logger.hpp"

class TestDay16 : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDay16);
    CPPUNIT_TEST(testErrorRate);
    CPPUNIT_TEST(testCorrectOrder);
    CPPUNIT_TEST(testInput);
    CPPUNIT_TEST_SUITE_END();

public:
    void testErrorRate(void);
    void testCorrectOrder(void);
    void testInput(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestDay16);

void TestDay16::testErrorRate(void)
{
    const std::string filename = "input/day16_test.txt";
    auto document = day16::Document(filename);
    int errorRate = document.getScanningErrorRate(true);
    CPPUNIT_ASSERT_EQUAL(71, errorRate);
}

void TestDay16::testCorrectOrder(void)
{
    const std::string filename = "input/day16_test2.txt";
    auto document = day16::Document(filename);
    auto correctOrder = document.extractCorrectOrder();
    const std::vector<std::string> refCorrectOrder = {"row", "class", "seat"};
    CPPUNIT_ASSERT_EQUAL(refCorrectOrder.size(), correctOrder.size());
    for (size_t index = 0; index < refCorrectOrder.size(); index++)
    {
        CPPUNIT_ASSERT_EQUAL(refCorrectOrder[index], correctOrder[index]);
    }
}

void TestDay16::testInput(void)
{
    const std::string filename = "input/day16.txt";
    int errorRate;
    long finalProduct;
    CPPUNIT_ASSERT_EQUAL(Ok, day16::execute(filename, errorRate, finalProduct));
    CPPUNIT_ASSERT_EQUAL(22977, errorRate);
    CPPUNIT_ASSERT_EQUAL(static_cast<long>(998358379943), finalProduct);
}