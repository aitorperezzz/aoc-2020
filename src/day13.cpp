#include <exception>
#include <numeric>

#include "day13.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

namespace day13
{

Problem::Problem(const std::vector<std::string> &lines, const Part part)
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
            busIds.push_back(std::stoi(innerString));
        }
        else if (part == TWO)
        {
            busIds.push_back(-1);
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

ErrorCode execute(const std::string &filename, int &result1, long &result2)
{
    // Load input
    std::vector<std::string> lines;
    if (FileOpener::loadVector(lines, filename) != Ok)
    {
        Logger::log("Could not read values from file", ERROR);
        return InvalidFile;
    }

    // Solve part one
    Problem problem(lines, ONE);
    result1 = problem.computeEarliestBusTimesWaitTime();
    Logger::log("Result of part one: " + std::to_string(result1), INFO);

    // Solve part two
    Problem problem2(lines, TWO);
    result2 = solvePartTwo(problem2.busIds);
    Logger::log("Minimal timestamp for part two: " + std::to_string(result2),
                INFO);

    return ErrorCode::Ok;
}

long multiplicativeInverse(const long a, const long n)
{
    long t = 0, newt = 1;
    long r = n, newr = a;

    long quotient, auxt, auxr;
    while (newr != 0)
    {
        quotient = r / newr;
        auxt = newt;
        newt = t - quotient * newt;
        t = auxt;
        auxr = newr;
        newr = r - quotient * newr;
        r = auxr;
    }

    if (r > 1)
    {
        throw std::logic_error("Number does not have inverse");
    }
    if (t < 0)
    {
        t = t + n;
    }
    return t;
}

long solveChineseTheorem(const std::vector<long> &results,
                         const std::vector<long> &divisors)
{
    // Compute the product of all divisors as an auxiliary variable
    long Nproduct =
        std::accumulate(divisors.cbegin(), divisors.cend(),
                        static_cast<long>(1), std::multiplies<long>());

    // Compute the multiplicative modular inverses of each of the equations, and
    // add to the solution
    long solution = 0;
    long ni;
    for (size_t i = 0; i < divisors.size(); i++)
    {
        ni = Nproduct / divisors[i];
        solution += results[i] * multiplicativeInverse(ni, divisors[i]) * ni;
    }

    // Returning the smallest positive possible solution
    return (solution % Nproduct + Nproduct) % Nproduct;
}

long solvePartTwo(const std::vector<int> &busIds)
{
    // Grab all the well defined bus ids and keep the "results" that will serve
    // the chinese theorem, on the fly. Convert to bigger integers
    std::vector<long> fixedResults;
    std::vector<long> fixedDivisors;
    for (size_t i = 0; i < busIds.size(); i++)
    {
        if (busIds[i] != -1)
        {
            fixedResults.push_back(static_cast<long>(0 - i));
            fixedDivisors.push_back(static_cast<long>(busIds[i]));
        }
    }

    return solveChineseTheorem(fixedResults, fixedDivisors);
}

} // namespace day13