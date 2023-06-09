#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "errorCode.hpp"

namespace day13
{

/// @brief Identifies the part of the problem we are solving
enum Part
{
    ONE,
    TWO
};

/// @brief Gathers all the information needed for the problem
struct Problem
{
    int arrivalTimestamp;
    std::vector<int> busIds;

    /// @brief Constructor. Throws exceptions
    Problem(const std::vector<std::string> &lines, const Part part);

    /// @brief Computes the product of the id of the bus I have to get
    /// times the waiting time (difference between the time the bus leaves
    /// minus the timestamp of arrival to the airport)
    int computeEarliestBusTimesWaitTime();
};

/// @brief Returns the results for the day
ErrorCode execute(const std::string &filename, int &result1, long &result2);

/// @brief Solves the Chinese remainder theorem given as a set of equations:
/// x = results[0] mod divisors[0]
/// ...
/// x = results[n] mod divisors[n]
/// @param[in] results Set of all the values to the left of the equal sign
/// @param[in] divisors Set of all the values after the mod sign
long solveChineseTheorem(const std::vector<long> &results,
                         const std::vector<long> &divisors);

/// @brief Receives the bus ids (with -1 instead of x) and returns the first
/// (positive) timestamp such that the buses leave at the order they are
/// programmed
long solvePartTwo(const std::vector<int> &busIds);

} // namespace day13