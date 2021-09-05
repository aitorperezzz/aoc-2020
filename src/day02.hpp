#pragma once

#include <string>

#include "errorCode.hpp"

// Struct that can hold all the relevant information from
// a password line in file.
struct PasswordInfo
{
	int minValue;
	int maxValue;
	char letter;
	std::string password;
};

class Day02
{

public:
	static ErrorCode execute(const std::string& filename, int& result1, int& result2);

private:
	static ErrorCode parseInfo(PasswordInfo& info, const std::string& line);
	static ErrorCode check1(size_t& counter, const PasswordInfo& info);
	static ErrorCode check2(size_t& counter, const PasswordInfo& info);
};