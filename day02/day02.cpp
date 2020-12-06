#include <vector>
#include <string>
#include <algorithm>

#include "day02.hpp"
#include "errorCode.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

ErrorCode Day02::execute(const std::string& filename, int& result1, int& result2)
{
	// Open the contents of the file as a vector of strings.
	std::vector<std::string> inStrings;
	if (FileOpener::loadVector(inStrings, filename) != Ok)
	{
		Logger::log("The input file could not be read", ERROR);
		return Error;
	}

	// Parse the strings into appropriate structures.
	size_t counter1 = 0, counter2 = 0;
	PasswordInfo info;
	for (auto i = inStrings.begin(); i != inStrings.end(); i++)
	{
		// Parse information from the password.
		if (Day02::parseInfo(info, *i) != Ok)
		{
			Logger::log("Could not parse information from a password", ERROR);
			return InternalInconsistency;
		}

		// Check if valid for part 1.
		if (check1(counter1, info) != Ok)
		{
			Logger::log("Could not check validity of password info, part 1", ERROR);
			return InternalInconsistency;
		}

		// Check if valid for part 2.
		if (check2(counter2, info) != Ok)
		{
			Logger::log("Could not check validity of password info, part 2", ERROR);
			return InternalInconsistency;
		}
	}

	// Log results and return to caller.
	Logger::log("Number of valid passwords, part 1: " + std::to_string(counter1), INFO);
	Logger::log("Number of valid passwords, part 2: " + std::to_string(counter2), INFO);
	result1 = counter1;
	result2 = counter2;
	return Ok;
}

ErrorCode Day02::parseInfo(PasswordInfo& info, const std::string& line)
{
	// Find the minimum value.
	size_t pos = line.find('-', 0);
	try
	{
		info.minValue = std::stoi(line.substr(0, pos));
	}
	catch(const std::exception& e)
	{
		Logger::log("Could not parse min num times", ERROR);
		return Error;
	}

	// Find the max value.
	size_t newpos = line.find(' ', pos);
	try
	{
		info.maxValue = std::stoi(line.substr(pos + 1, newpos));
	}
	catch(const std::exception& e)
	{
		Logger::log("Could not parse max num times", ERROR);
		return Error;
	}

	// Find the letter.
	info.letter = line[newpos + 1];

	// Find the password.
	pos = newpos + 1;
	newpos = line.find(' ', pos);
	info.password = line.substr(newpos + 1);

	return Ok;
}

ErrorCode Day02::check1(size_t& counter, const PasswordInfo& info)
{
	int numRepeat = std::count(info.password.begin(), info.password.end(),
		info.letter);

	// Check if password is valid.
	if (info.minValue <= numRepeat && numRepeat <= info.maxValue)
	{
		counter++;
	}
	
	return Ok;
}

ErrorCode Day02::check2(size_t& counter, const PasswordInfo& info)
{
	bool first = info.password[info.minValue - 1] == info.letter;
	bool second	= info.password[info.maxValue - 1] == info.letter;
	if ((first && !second) || (!first && second))
	{
		counter++;
	}

	return Ok;
}