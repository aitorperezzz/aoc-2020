#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "errorCode.hpp"

namespace day13
{

/// @brief Gathers all the information needed for the problem
struct Problem
{
    int arrivalTimestamp;
    std::vector<int> busIds;

    /// @brief Constructor. Throws exceptions
    Problem(const std::vector<std::string> &lines);

    /// @brief Computes the product of the id of the bus I have to get
    /// times the waiting time (difference between the time the bus leaves
    /// minus the timestamp of arrival to the airport)
    int computeEarliestBusTimesWaitTime();
};

/// @brief Returns the results for the day
ErrorCode execute(const std::string &filename, int &result);

} // namespace day13