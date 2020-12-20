#pragma once

#include <string>
#include <vector>

#include "errorCode.hpp"

class Day09
{

public:
	static ErrorCode execute(const std::string& filename,
		const int preambleSize,
		unsigned long& result1,
		unsigned long& result2);

private:
	static ErrorCode findOddNumber(unsigned long& result,
		const std::vector<unsigned long>& values,
		const int preambleSize);
	static ErrorCode findBlock(unsigned long& result2,
	const unsigned long& result1,
	const std::vector<unsigned long>& values);
};