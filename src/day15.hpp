#pragma once

#include <vector>

#include "errorCode.hpp"

namespace day15
{

/// @brief Returns the results for the day
ErrorCode execute(const std::vector<int> &startingNumbers, const int iterations,
                  int &result);

} // namespace day15