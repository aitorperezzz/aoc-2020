#include <cmath>

#include "day05.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

#define NUM_ROWS 128
#define NUM_COLS 8

ErrorCode Day05::execute(const std::string&filename, short& result1, short& result2)
{
	// Open the contents of the file.
	std::vector<std::string> passes;
	if (FileOpener::loadVector(passes, filename) != Ok)
	{
		Logger::log("Could not open file with boarding passes", ERROR);
		return InvalidFile;
	}

	// Create a double array that will inform if a seat is in the list
	// of boarding passes.
	std::vector<std::vector<bool>> plane;
	plane.resize(NUM_ROWS);
	for (size_t i = 0; i < NUM_ROWS; i++)
	{
		plane[i].resize(NUM_COLS);
		for (size_t j = 0; j < NUM_COLS; j++)
		{
			plane[i][j] = false;
		}
	}

	// Loop over all boarding passes, getting the row and col of the ones found,
	// and checking the ID to find the highest one.
	short row, col;
	short highestID = 0, newID;
	for (auto pass = passes.begin(); pass != passes.end(); pass++)
	{
		// Get the seat ID and fill in the row and col.
		newID = getSeatID(*pass, row, col);

		// If this seat has higher ID than the previous one, keep
		// it as the highest one.
		highestID = newID > highestID ? newID : highestID;

		// Mark the seat with current row and column as present in the plane.
		plane[row][col] = true;
	}

	// Result for the first part
	Logger::log("The highest ID found is: " + std::to_string(highestID), INFO);
	result1 = highestID;

	// Find the ID of the seat that is missing in the plane.
	if (findMissingSeatID(plane, result2) != Ok)
	{
		Logger::log("Could not find ID of the missing seat", ERROR);
		return Error;
	}
	Logger::log("The ID of the missing seat is: " + std::to_string(result2), INFO);
	return Ok;
}

// This function will return the ID of a seat,
// and fill in the row and col as well.
short Day05::getSeatID(const std::string& pass, short& row, short& col)
{
	// Get row and col of the seat.
	row = parseBinary(pass.substr(0, 7), 'F');
	col = parseBinary(pass.substr(7, 3), 'L');

	// Calculate the seat ID.
	return 8 * row + col;
}

short Day05::parseBinary(const std::string& repr, const char zeroSymbol)
{
	std::string binary = "";
	for (size_t i = 0, n = repr.length(); i < n; i++)
	{
		binary += repr[i] == zeroSymbol ? '0' : '1';
	}

	return std::stoi(binary, nullptr, 2);
}

ErrorCode Day05::findMissingSeatID(const std::vector<std::vector<bool>>& plane,
	short& seatId)
{
	// Loop over all seats of the plane to find a missing one.
	for (size_t i = 0; i < NUM_ROWS; i++)
	{
		for (size_t j = 0; j < NUM_COLS; j++)
		{
			if (plane[i][j] == false)
			{
				// Check the previous row and next row exist and are full.
				if (checkRow(i - 1, plane) && checkRow(i + 1, plane))
				{
					seatId = i * 8 + j;
					return Ok;
				}
			}
		}
	}

	return Error;
}

bool Day05::checkRow(const size_t row, const std::vector<std::vector<bool>>& plane)
{
	if (row < 0 || row >= NUM_ROWS)
	{
		return false;
	}

	for (size_t j = 0; j < NUM_COLS; j++)
	{
		if (plane[row][j] == false)
		{
			return false;
		}
	}

	return true;
}