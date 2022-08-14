#pragma once

#include <string>

#include "errorCode.hpp"

namespace day11
{

enum State
{
    FLOOR,
    EMPTY,
    OCCUPIED
};

ErrorCode execute(const std::string &filename, unsigned int &result1,
                  unsigned int &result2);

bool applyRules(const size_t part, std::vector<std::vector<State>> &layout,
                size_t &totalOccupied);

size_t countAdjacentOccupied(const std::vector<std::vector<State>> &layout,
                             const int icenter, const int jcenter);

size_t countLinedOccupied(const std::vector<std::vector<State>> &layout,
                          const int icenter, const int jcenter);

} // namespace day11