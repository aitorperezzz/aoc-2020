#include "day01.hpp"
#include "day02.hpp"
#include "day03.hpp"
#include "day04.hpp"
#include "day05.hpp"
#include "day06.hpp"
#include "day07.hpp"
#include "day08.hpp"
#include "day09.hpp"
#include "day10.hpp"
#include "logger.hpp"

int main(int argc, char *argv[])
{
    // Check only one command line parameter was provided
    if (argc != 2)
    {
        Logger::log(
            "Please provide one command line argument that identifies the "
            "number day",
            ERROR);
        return -1;
    }

    // Check the command line argument is an integer
    std::string argumentString = std::string(argv[1]);
    for (size_t i = 0; i < argumentString.length(); i++)
    {
        if (!std::isdigit(argumentString[i]))
        {
            Logger::log("Argument provided does not look like an integer: " +
                            argumentString,
                        ERROR);
        }
    }
    int day = atoi(argv[1]);

    // Execute depending on the day requested
    switch (day)
    {
    case 1: {
        int result;
        if (Day01::executePartOne("./input/day01.txt", result) != Ok)
        {
            return -1;
        }

        if (Day01::executePartTwo("./input/day01.txt", result) != Ok)
        {
            return -1;
        }
        break;
    }
    case 2: {
        int result1, result2;
        if (Day02::execute("./input/day02.txt", result1, result2) != Ok)
        {
            return -1;
        }
        break;
    }
    case 3: {
        int result1;
        unsigned long result2;
        if (Day03::execute("./input/day03.txt", result1, result2) != Ok)
        {
            return -1;
        }
        break;
    }
    case 4: {
        int result1, result2;
        if (Day04::execute("./input/day04.txt", result1, result2) != Ok)
        {
            return -1;
        }
        break;
    }
    case 5: {
        short result1, result2;
        if (Day05::execute("./input/day05.txt", result1, result2) != Ok)
        {
            return -1;
        }
        break;
    }
    case 6: {
        short result1, result2;
        if (Day06::execute("./input/day06.txt", result1, result2) != Ok)
        {
            return -1;
        }
        break;
    }
    case 7: {
        int result1, result2;
        if (Day07::execute("./input/day07.txt", result1, result2) != Ok)
        {
            return -1;
        }
        break;
    }
    case 8: {
        int result1, result2;
        if (Day08::execute("./input/day08.txt", result1, result2) != Ok)
        {
            return -1;
        }
        break;
    }
    case 9: {
        unsigned long result1, result2;
        if (Day09::execute("./input/day09.txt", 25, result1, result2) != Ok)
        {
            return -1;
        }
        break;
    }
    case 10: {
        unsigned long result1, result2;
        if (Day10::execute("input/day10.txt", result1, result2) != Ok)
        {
            return -1;
        }
        break;
    }
    default:
        Logger::log("Day is not supported: " + std::to_string(day), ERROR);
        return -1;
    }

    return 0;
}