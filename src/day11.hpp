#pragma once

#include <string>

#include "errorCode.hpp"

enum State
{
    FLOOR,
    EMPTY,
    OCCUPIED
};

class Day11
{
public:
    static ErrorCode execute(const std::string &filename, unsigned int &result1,
                             unsigned int &result2);

private:
    static bool applyRules(const size_t part,
                           std::vector<std::vector<State>> &layout,
                           size_t &totalOccupied);
    static size_t countAdjacentOccupied(
        const std::vector<std::vector<State>> &layout, const int icenter,
        const int jcenter);
    static size_t countLinedOccupied(
        const std::vector<std::vector<State>> &layout, const int icenter,
        const int jcenter);
};