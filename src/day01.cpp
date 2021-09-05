#include "day01.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

ErrorCode Day01::executePartOne(const std::string &filename, int &result)
{
    // Open the values in the text file into an int vector.
    std::vector<int> values;
    if (FileOpener::loadVector(values, filename) != Ok)
    {
        Logger::log("Could not read values from file", ERROR);
        return InvalidFile;
    }

    // Go through pairs of them, checking if the sum is 2020.
    size_t length = values.size();
    for (size_t i = 0; i < length; i++)
    {
        for (size_t j = i + 1; j < length; j++)
        {
            if ((values[i] + values[j]) == 2020)
            {
                Logger::log("Two values have been found that sum 2020", INFO);
                Logger::log("The product of both is " +
                                std::to_string(values[i] * values[j]),
                            INFO);
                result = values[i] * values[j];
                return Ok;
            }
        }
    }

    // The requested values have not been found.
    Logger::log("No values have been found that sum 2020", ERROR);
    return InternalInconsistency;
}

ErrorCode Day01::executePartTwo(const std::string &filename, int &result)
{
    // Open the values in the text file into an int vector.
    std::vector<int> values;
    if (FileOpener::loadVector(values, filename) != Ok)
    {
        Logger::log("Could not read values from file", ERROR);
        return InvalidFile;
    }

    // Go through sets of three values, checking if the sum is 2020.
    size_t length = values.size();
    for (size_t i = 0; i < length; i++)
    {
        for (size_t j = i + 1; j < length; j++)
        {
            for (size_t k = j + 1; k < length; k++)
            {
                if ((values[i] + values[j] + values[k]) == 2020)
                {
                    Logger::log("Three values have been found that sum 2020",
                                INFO);
                    Logger::log(
                        "The product of them is " +
                            std::to_string(values[i] * values[j] * values[k]),
                        INFO);
                    result = values[i] * values[j] * values[k];
                    return Ok;
                }
            }
        }
    }

    // The requested values have not been found.
    Logger::log("No values have been found that sum 2020", ERROR);
    return InternalInconsistency;
}