#include <exception>

#include "day13.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

namespace day13
{

Problem::Problem(const std::vector<std::string> &lines)
{
    // Input file needs to have two lines only
    if (lines.size() != 2)
    {
        throw std::range_error("Size of vector not expected");
    }

    // First line is the arrival timestamp
    arrivalTimestamp = std::stoi(lines[0]);

    // Next line contains the ids of the buses available
    std::string delimiter = ",";
    std::string busList = lines[1];
    while (true)
    {
        // Get next delimiter
        size_t pos = busList.find(delimiter);
        // If I reached the end of the string, I still need to get the last
        // value
        if (pos == std::string::npos)
        {
            pos = busList.length();
        }

        // If the inner string found is x, just continue, else process it
        std::string innerString = busList.substr(0, pos);
        if (innerString != "x")
        {
            int id = std::stoi(innerString);
            busIds.push_back(id);
        }

        // If this is the end, just break out of the loop
        if (pos == busList.length())
        {
            break;
        }

        // Update the list removing everything until the delimiter
        busList = busList.substr(pos + 1, busList.length());
    }
}

int Problem::computeEarliestBusTimesWaitTime()
{
    int timestamp = arrivalTimestamp;
    while (true)
    {
        for (const auto id : busIds)
        {
            if (timestamp % id == 0)
            {
                return id * (timestamp - arrivalTimestamp);
            }
        }
        timestamp++;
    }
}

ErrorCode execute(const std::string &filename, int &result)
{
    // Load input
    std::vector<std::string> lines;
    if (FileOpener::loadVector(lines, filename) != Ok)
    {
        Logger::log("Could not read values from file", ERROR);
        return InvalidFile;
    }

    // Parse input
    Problem problem(lines);

    // Compute the earliest bus
    result = problem.computeEarliestBusTimesWaitTime();
    Logger::log("Result of part one: " + std::to_string(result), INFO);
    return ErrorCode::Ok;
}

} // namespace day13