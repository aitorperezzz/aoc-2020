#include <iostream>
#include <map>

#include "day15.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

namespace day15
{

ErrorCode execute(const std::vector<int> &startingNumbers, const int iterations,
                  int &result)
{
    // Fill in the starting numbers
    std::vector<int> position(iterations);
    std::vector<int> count(iterations, 0);
    int start = static_cast<int>(startingNumbers.size());
    for (int i = 0; i < start; i++)
    {
        position[startingNumbers[i]] = i;
        count[startingNumbers[i]] = 1;
    }

    // Some variables declared here
    int previous = startingNumbers.back();
    int current = 0;
    for (int i = start; i < iterations; i++)
    {
        // The current number has its count updated, so check its value
        if (count[current] == 1)
        {
            // This is the first time the number had been spoken, so say
            // zero
            current = 0;
            count[0]++;
        }
        else
        {
            // The number had been spoken before, so say the difference
            current = i - 1 - position[previous];
            count[current]++;
        }

        // Only update now the position, but of the previous number
        position[previous] = i - 1;
        previous = current;
    }

    Logger::log("Final result: " + std::to_string(current), INFO);
    result = current;
    return ErrorCode::Ok;
}
} // namespace day15