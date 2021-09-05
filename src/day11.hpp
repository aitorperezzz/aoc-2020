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
    static ErrorCode execute(const std::string &filename, unsigned int &result);

private:
    static bool applyRules(std::vector<std::vector<State>> &layout,
                           size_t &totalOccupied);
    static size_t countAdjacentOccupied(
        const std::vector<std::vector<State>> &layout, const int icenter,
        const int jcenter);
};