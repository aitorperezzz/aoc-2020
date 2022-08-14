#pragma once

#include <map>
#include <set>
#include <string>

#include "errorCode.hpp"

namespace day07
{

typedef std::map<std::string, int> Rule;

ErrorCode execute(const std::string &filename, int &result1, int &result2);

} // namespace day07