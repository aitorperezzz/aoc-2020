#include <vector>
#include <numeric>

#include "day03.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

ErrorCode Day03::execute(const std::string& filename, int& result1,
	unsigned long& result2)
{
	// Load inputs from file.
	std::vector<std::string> map;
	if (FileOpener::loadVector(map, filename) != Ok)
	{
		Logger::log("Map could not be loaded from input file", ERROR);
		return InvalidFile;
	}

	// Create all the slopes to check.
	std::vector<std::pair<size_t, size_t>> slopes;
	slopes.push_back(std::make_pair(1, 1));
	slopes.push_back(std::make_pair(3, 1));
	slopes.push_back(std::make_pair(5, 1));
	slopes.push_back(std::make_pair(7, 1));
	slopes.push_back(std::make_pair(1, 2));
	size_t numSlopes = slopes.size();

	// Loop over all slopes and count the number of trees.
	std::vector<unsigned long> numTrees;
	numTrees.resize(numSlopes);
	for (size_t i = 0; i < numSlopes; i++)
	{
		if (Day03::numberTrees(map, slopes[i], numTrees[i]) != Ok)
		{
			Logger::log("Could not count num trees on a slope", ERROR);
			return Error;
		}
	}

	// Show result for part one.
	Logger::log("Trees encountered: " + std::to_string(numTrees[1]), INFO);
	result1 = numTrees[1];

	// Calculate the product of all the slopes.
	unsigned long product = 1;
	for (size_t i = 0; i < numSlopes; i++)
	{
		product *= numTrees[i];
	}

	// Result for part two.
	Logger::log("Product for all slopes: " + std::to_string(product), INFO);
	result2 = product;
	return Ok;
}

ErrorCode Day03::numberTrees(const std::vector<std::string>& map,
	std::pair<size_t, size_t>& slope, unsigned long& result)
{
	// Loop over all the rows.
	size_t currentRow = 0, currentCol = 0;
	size_t numRows = map.size(), numCols = map[0].size();
	unsigned long counter = 0;
	while (currentRow < numRows)
	{
		// Check if the current spot is a tree.
		if (map[currentRow][currentCol] == '#')
		{
			counter++;
		}

		// Update current row and col.
		currentRow += slope.second;
		currentCol = (currentCol + slope.first) % numCols;
	}

	result = counter;
	return Ok;
}