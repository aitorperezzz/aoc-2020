#include <vector>
#include <algorithm>
#include <iostream>

#include "day10.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

ErrorCode Day10::execute(const std::string& filename, int& result1,
	int& result2)
{
	// Open input file.
	std::vector<int> values;
	if (FileOpener::loadVector(values, filename) != Ok)
	{
		Logger::log("Could not read values from file", ERROR);
		return InvalidFile;
	}

	// Sort all values in the vector.
	std::sort(values.begin(), values.end());

	// Insert the first outlet adapter and the last
	// device adapter.
	values.insert(values.begin(), 0);
	values.push_back(*(std::max_element(values.begin(), values.end())) + 3);

	// Check the chain of adapters is valid and count.
	if (checkAndCount(values, result1) != Ok)
	{
		Logger::log("The chain of adapters provided is not valid", ERROR);
		return NoSolution;
	}
	Logger::log("Result for part one is: " + std::to_string(result1), INFO);

	// Compute the reuslt of part two.
	if (numArrangements(values, result2) != Ok)
	{
		Logger::log("Could not compute number of arrangements", ERROR);
		return NoSolution;
	}
	Logger::log("Result of part two is " + std::to_string(result2), INFO);
	return Ok;
}

ErrorCode Day10::checkAndCount(const std::vector<int>& values,
	int& result)
{
	int counter1 = 0, counter3 = 0;
	for (auto it = values.begin(); it != values.end() - 1; it++)
	{
		if (*(it + 1) - *it > 3)
		{
			return InvalidArgument;
		}
		else if (*(it + 1) - *it == 1)
		{
			counter1++;
		}
		else if (*(it + 1) - *it == 3)
		{
			counter3++;
		}
	}

	result = counter1 * counter3;
	return Ok;
}

ErrorCode Day10::numArrangements(const std::vector<int>& values,
	int& result)
{
	int count = 1;
	auto begin = values.begin(), current = values.begin();
	while (current != values.end() - 1)
	{
		// If the distance to the next adapter is 3, we close the range.
		if (*(current + 1) - *current == 3)
		{
			int inter = countFromTo(begin, current + 1);
			count *= inter;
			std::cout << "got inter value: " << inter << std::endl;
			std::cout << "current global count: " << count << std::endl;
			begin = current + 1;
		}
		current++;
	}

	result = count;
	return Ok;
}

// Count all the possibilities in which begin
// is always at the beginning of the combination.
int Day10::countFromTo(const std::vector<int>::const_iterator& begin,
	const std::vector<int>::const_iterator& end)
{
	std::cout << "\nStarting count from " << *begin << " to " << *(end - 1) << std::endl;

	// Nothing to do if we are at the end.
	if (*begin + 3 == *end)
	{
		return 0;
	}

	// First there is only one possibility.	
	int count = 1;

	// Skip until we can.
	auto current = begin + 1;
	while (current != end)
	{
		if (*current - *begin < 3)
		{
			// This is valid. There is the combination with begin,
			// current, and then all the rest.
			count += countFromTo(current, end);
		}
		std::cout << "Update current from " << *current << " to " << *(current + 1)	 << std::endl;
		current++;
	}
	std::cout << "Count from " << *begin << " to " << *(end-1) << std::endl;
	std::cout << count << std::endl;
	return count;
}