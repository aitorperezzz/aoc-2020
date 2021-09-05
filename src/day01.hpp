#pragma once

#include <string>

#include "errorCode.hpp"

class Day01
{

public:
	static ErrorCode executePartOne(const std::string& filename, int& result);
	static ErrorCode executePartTwo(const std::string& filename, int& result);
};