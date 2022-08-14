#pragma once

#include <string>

#include "errorCode.hpp"

namespace day17
{

/// @brief Returns the results for the day
ErrorCode execute(const std::string &filename, int &result1, int &result2);

} // namespace day17