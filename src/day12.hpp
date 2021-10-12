#pragma once

#include <iostream>
#include <string>

#include "errorCode.hpp"

namespace day12
{

struct Instruction
{
    // Constructor
    Instruction(const char inAction, const int inValue)
    {
        action = inAction;
        value = inValue;
    }

    // Log the action in a simple way
    std::string log() const
    {
        std::string output = "action: ";
        output += action;
        return output + "; value: " + std::to_string(value);
    }

    // Action of the instruction
    char action;

    // Value of the instruction
    int value;
};

struct Ship
{
    int xpos = 0;
    int ypos = 0;
    int xdirection = 0;
    int ydirection = 0;

    Ship(const bool withWaypoint)
    {
        if (withWaypoint)
        {
            xdirection = 10;
            ydirection = 1;
        }
        else
        {
            xdirection = 1;
            ydirection = 0;
        }
    }

    // Apply provided instruction to the ship
    ErrorCode applyInstruction(const Instruction &instruction);

    // Apply provided instruction to the ship
    ErrorCode applyInstructionWithWaypoint(const Instruction &instruction);

    // Log ship status
    std::string log() const
    {
        return "Position: [" + std::to_string(xpos) + ", " +
               std::to_string(ypos) + "], Direction: [" +
               std::to_string(xdirection) + ", " + std::to_string(ydirection) +
               "]";
    }

    // Calculate Manhattan distance
    inline uint32_t getManhattanDistance() const
    {
        return std::abs(xpos) + std::abs(ypos);
    }
};

ErrorCode execute(const std::string &filename, uint32_t &result1,
                  uint32_t &result2);

} // namespace day12