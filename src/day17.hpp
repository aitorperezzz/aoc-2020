#pragma once

#include <string>

#include "errorCode.hpp"

namespace day17
{

/// @brief Returns the results for the day
ErrorCode execute(const std::string &filename, size_t &result1,
                  size_t &result2);

} // namespace day17