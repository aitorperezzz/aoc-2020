#pragma once

#include <string>

#include "errorCode.hpp"

namespace day18
{

enum Math
{
    Basic,
    Advanced
};

/// @brief Return the result of an operation given as a string, with the
/// provided type of math
std::string compute(const std::string &operation, const Math math);

/// @brief Returns the result of a problem given inside a file
ErrorCode execute(const std::string &filename, long &result1, long &result2);

} // namespace day18