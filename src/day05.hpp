#pragma once

#include <string>
#include <vector>

#include "errorCode.hpp"

class Day05
{

public:
	static ErrorCode execute(const std::string&filename,
		short& result1, short& result2);

	static short getSeatID(const std::string& pass, short& row, short& col);
	static short parseBinary(const std::string& repr, const char zeroSymbol);

	static ErrorCode findMissingSeatID(const std::vector<std::vector<bool>>& plane,
		short& seatId);
	static bool checkRow(const size_t row, const std::vector<std::vector<bool>>& plane);
};