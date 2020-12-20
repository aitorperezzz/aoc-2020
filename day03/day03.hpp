#pragma once

#include <string>
#include <vector>

#include "errorCode.hpp"

class Day03
{

public:
	static ErrorCode execute(const std::string& filename, int& result1,
		unsigned long& result2);

private:
	static ErrorCode numberTrees(const std::vector<std::string>& map,
		std::pair<size_t, size_t>& slope, unsigned long& result);
};