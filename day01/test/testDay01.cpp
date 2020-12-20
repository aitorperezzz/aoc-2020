#include "cppunit/TestFixture.h"
#include "cppunit/TestCase.h"
#include "cppunit/extensions/HelperMacros.h"

#include "day01.hpp"
#include "logger.hpp"

class TestDay01 : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestDay01);
	CPPUNIT_TEST(testTestFile);
	CPPUNIT_TEST(testInputFile);
	CPPUNIT_TEST_SUITE_END();

public:
	void testTestFile(void);
	void testInputFile(void);
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestDay01);

void TestDay01::testTestFile(void)
{
	Logger::setSilentMode();

	// Test with the test file first.
	std::string filename = "input/test.txt";
	int result;
	if (Day01::executePartOne(filename, result) != Ok)
	{
		CPPUNIT_ASSERT(false);
	}
	CPPUNIT_ASSERT_EQUAL(result, 514579);

	if (Day01::executePartTwo(filename, result) != Ok)
	{
		CPPUNIT_ASSERT(false);
	}
	CPPUNIT_ASSERT_EQUAL(result, 241861950);
}

void TestDay01::testInputFile(void)
{
	Logger::setSilentMode();

	// Now test the input file.
	std::string filename = "input/input.txt";
	int result;
	if (Day01::executePartOne(filename, result) != Ok)
	{
		CPPUNIT_ASSERT(false);
	}
	CPPUNIT_ASSERT_EQUAL(result, 482811);

	if (Day01::executePartTwo(filename, result) != Ok)
	{
		CPPUNIT_ASSERT(false);
	}
	CPPUNIT_ASSERT_EQUAL(result, 193171814);
}