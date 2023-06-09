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
#include "day11.hpp"
#include "day12.hpp"
#include "day13.hpp"
#include "day14.hpp"
#include "day15.hpp"
#include "day16.hpp"
#include "day17.hpp"
#include "day18.hpp"
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
            return -1;
        }
    }
    int day = atoi(argv[1]);

    // Execute depending on the day requested
    switch (day)
    {
    case 1: {
        int result;
        if (day01::executePartOne("./input/day01.txt", result) != Ok)
        {
            return -1;
        }

        if (day01::executePartTwo("./input/day01.txt", result) != Ok)
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
        if (day07::execute("./input/day07.txt", result1, result2) != Ok)
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
    case 11: {
        unsigned int result1, result2;
        if (day11::execute("input/day11.txt", result1, result2) != Ok)
        {
            return -1;
        }
        break;
    }
    case 12: {
        uint32_t result1, result2;
        if (day12::execute("input/day12.txt", result1, result2) != Ok)
        {
            return -1;
        }
        break;
    }
    case 13: {
        int result1;
        long result2;
        if (day13::execute("input/day13.txt", result1, result2) != Ok)
        {
            return -1;
        }
        break;
    }
    case 14: {
        unsigned long result;
        if (day14::execute("input/day14.txt", day14::Version::ONE, result) !=
            Ok)
        {
            return -1;
        }
        if (day14::execute("input/day14.txt", day14::Version::TWO, result) !=
            Ok)
        {
            return -1;
        }
        break;
    }
    case 15: {
        const int iterations = 30000000;
        int result;
        std::vector<int> startingNumbers = {14, 8, 16, 0, 1, 17};
        if (day15::execute(startingNumbers, iterations, result) != Ok)
        {
            return -1;
        }
        break;
    }
    case 16: {
        int errorRate;
        long finalProduct;
        if (day16::execute("input/day16.txt", errorRate, finalProduct) != Ok)
        {
            return -1;
        }
        break;
    }
    case 17: {
        size_t result1, result2;
        if (day17::execute("input/day17.txt", result1, result2) != Ok)
        {
            return -1;
        }
        break;
    }
    case 18: {
        long result1, result2;
        if (day18::execute("input/day18.txt", result1, result2) != Ok)
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