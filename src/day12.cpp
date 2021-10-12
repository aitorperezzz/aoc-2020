#include <algorithm>
#include <iostream>
#include <vector>

#include "day12.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

namespace day12
{

enum Direction
{
    Right,
    Left
};

int calculateNumRotations(const int completeAngle)
{
    if (completeAngle % 90 != 0)
    {
        throw std::out_of_range("Angle is not valid");
    }
    return completeAngle / 90;
}

ErrorCode rotateVector90degrees(int &x, int &y, const int numTimes,
                                const Direction &direction)
{
    int auxx = x, auxy = y;
    int tempx;
    for (int i = 0; i < numTimes; i++)
    {
        if (direction == Left)
        {
            tempx = auxx;
            auxx = -auxy;
            auxy = tempx;
        }
        else
        {
            tempx = auxx;
            auxx = auxy;
            auxy = -tempx;
        }
    }
    x = auxx;
    y = auxy;
    return Ok;
}

ErrorCode execute(const std::string &filename, uint32_t &result1,
                  uint32_t &result2)
{
    // Load input file.
    std::vector<std::string> aux;
    if (FileOpener::loadVector(aux, filename) != Ok)
    {
        Logger::log("Could not read values from file", ERROR);
        return InvalidFile;
    }

    // Parse instructions
    std::vector<Instruction> instructions;
    instructions.reserve(aux.size());
    for (const auto &instructionString : aux)
    {
        instructions.emplace_back(instructionString[0],
                                  atoi(instructionString.c_str() + 1));
    }

    // Create a ship and a waypoint ship in their initial states
    Ship ship(false);
    Ship waypointShip(true);

    // Apply instructions to both ships
    for (const Instruction &instruction : instructions)
    {
        if (ship.applyInstruction(instruction) != Ok)
        {
            Logger::log("Could not apply instruction to ship:", ERROR);
            Logger::log(instruction.log(), ERROR);
            return ErrorCode::InternalInconsistency;
        }
        if (waypointShip.applyInstructionWithWaypoint(instruction) != Ok)
        {
            Logger::log("Could not apply instruction to waypoint ship:", ERROR);
            Logger::log(instruction.log(), ERROR);
            return ErrorCode::InternalInconsistency;
        }
    }

    // Get the final Manhattan distance and print it
    uint32_t distance1 = ship.getManhattanDistance();
    uint32_t distance2 = waypointShip.getManhattanDistance();
    Logger::log("Final Manhattan distance of the ship is: " +
                    std::to_string(distance1),
                INFO);
    Logger::log("Final Manhattan distance of the waypoint ship is: " +
                    std::to_string(distance2),
                INFO);
    result1 = distance1;
    result2 = distance2;
    return Ok;
}

ErrorCode Ship::applyInstruction(const Instruction &instruction)
{
    if (instruction.action == 'N')
    {
        ypos += instruction.value;
    }
    else if (instruction.action == 'S')
    {
        ypos -= instruction.value;
    }
    else if (instruction.action == 'E')
    {
        xpos += instruction.value;
    }
    else if (instruction.action == 'W')
    {
        xpos -= instruction.value;
    }
    else if (instruction.action == 'L')
    {
        rotateVector90degrees(xdirection, ydirection,
                              calculateNumRotations(instruction.value), Left);
    }
    else if (instruction.action == 'R')
    {
        rotateVector90degrees(xdirection, ydirection,
                              calculateNumRotations(instruction.value), Right);
    }
    else if (instruction.action == 'F')
    {
        for (int t = 0; t < instruction.value; t++)
        {
            xpos += xdirection;
            ypos += ydirection;
        }
    }
    else
    {
        Logger::log("Instruction action not recognised", ERROR);
        return InternalInconsistency;
    }

    return Ok;
}

ErrorCode Ship::applyInstructionWithWaypoint(const Instruction &instruction)
{
    if (instruction.action == 'N')
    {
        ydirection += instruction.value;
    }
    else if (instruction.action == 'S')
    {
        ydirection -= instruction.value;
    }
    else if (instruction.action == 'E')
    {
        xdirection += instruction.value;
    }
    else if (instruction.action == 'W')
    {
        xdirection -= instruction.value;
    }
    else
    {
        applyInstruction(instruction);
    }

    return Ok;
}

} // namespace day12