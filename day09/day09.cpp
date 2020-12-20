#include <vector>
#include <set>
#include <numeric>
#include <iostream>
#include <algorithm>

#include "day09.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

ErrorCode Day09::execute(const std::string& filename, const int preambleSize,
	unsigned long& result1, unsigned long& result2)
{
	// Open input file.
	std::vector<unsigned long> values;
	if (FileOpener::loadVector(values, filename) != Ok)
	{
		Logger::log("Could not read values from file", ERROR);
		return InvalidFile;
	}

	// Find the number that doesn't fullfill the rule.
	if (findOddNumber(result1, values, preambleSize) != Ok)
	{
		Logger::log("Could not find the odd number", ERROR);
		return NoSolution;
	}
	Logger::log("The odd number is: " + std::to_string(result1), INFO);

	// For the second part, find a contiguous block of numbers that
	// sum to the number just obtained.
	if (findBlock(result2, result1, values) != Ok)
	{
		Logger::log("Could not find the block of numbers for part two", ERROR);
		return NoSolution;
	}
	Logger::log("The encryption weakness is: " +
		std::to_string(result2), INFO);
	return Ok;
}

ErrorCode Day09::findOddNumber(unsigned long& result, const std::vector<unsigned long>& values,
	const int preambleSize)
{
	// Get an iterator to the element right after the preamble.
	std::vector<unsigned long>::const_iterator it = values.begin() + preambleSize;

	// Loop while the iterator does not reach the end.
	std::vector<unsigned long>::const_iterator subit1, subit2;
	bool foundValid;
	while (it != values.end())
	{
		foundValid = false;
		for (subit1 = it - preambleSize; subit1 != it; subit1++)
		{
			for (subit2 = subit1 + 1; subit2 != it; subit2++)
			{
				if (*subit1 + *subit2 == *it)
				{
					foundValid = true;
					break;
				}
			}

			if (foundValid)
			{
				break;
			}
		}

		if (!foundValid)
		{
			result = *it;
			return Ok;
		}

		it++;
	}

	// If here, all values fullfill the norm.
	return NoSolution;
}

ErrorCode Day09::findBlock(unsigned long& result2,
	const unsigned long& result1, const std::vector<unsigned long>& values)
{
	auto minit = values.begin(), maxit = minit + 2;
	unsigned long sum = 0;

	while ((sum = std::accumulate(minit, maxit, 0)) != result1)
	{
		if (sum < result1)
		{
			maxit++;
		}
		else
		{
			minit++;
		}
	}

	result2 = *std::min_element(minit, maxit) + 
		*std::max_element(minit, maxit);
	return Ok;
}