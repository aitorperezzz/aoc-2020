#include <fstream>
#include <string>

#include "fileOpener.hpp"
#include "logger.hpp"

template <typename T>
ErrorCode FileOpener::loadVector(std::vector<T>& outVector,
	const std::string& filename, const bool isColumn)
{
	// Open file to read.
	std::string line;
	std::ifstream file(filename);
	if (!file.is_open())
	{
		Logger::log("File " + filename + " could not be opened", ERROR);
		return InvalidFile;
	}
	
	// Read line after line.
	T newValue;
	outVector.empty();
	while (std::getline(file, line))
	{
		if (transformValue(line, newValue) != Ok)
		{
			Logger::log("Could not perform a value transformation", ERROR);
			return Error;
		}
		outVector.push_back(newValue);
	}

	// Close the file and quit.
	Logger::log("Succesfully read from file", INFO);
	file.close();
	return Ok;
}

// Define all the possible uses of the template loadVector function.
// string
template ErrorCode FileOpener::loadVector(std::vector<std::string>& outVector,
	const std::string& filename, const bool isColumn);
// int
template ErrorCode FileOpener::loadVector(std::vector<int>& outVector,
	const std::string& filename, const bool isColumn);

ErrorCode FileOpener::transformValue(const std::string& value, std::string& result)
{
	result = value;
	return Ok;
}

ErrorCode FileOpener::transformValue(const std::string& value, int& result)
{
	// Try to convert the current line to an integer.
	try
	{
		result = std::stoi(value, nullptr, 10);
	}
	catch(const std::exception& e)
	{
		Logger::log("Could not transform string to integer", ERROR);
		Logger::log(e.what(), ERROR);
		return InternalInconsistency;
	}
	
	// Add the new value to the provided vector.
	return Ok;
}