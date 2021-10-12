#include <algorithm>
#include <iostream>
#include <vector>

#include "day12.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

namespace day12
{

std::vector<int> possibleViewValues = {0, 90, 180, 270};

ErrorCode execute(const std::string &filename, uint32_t &result)
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

    // Create a ship in an initial state
    Ship ship;
    ship.viewAngle = 0;
    ship.xpos = 0;
    ship.ypos = 0;

    // Apply instructions
    for (const Instruction &instruction : instructions)
    {
        if (ship.applyInstruction(instruction) != Ok)
        {
            Logger::log("Could not apply instruction:", ERROR);
            Logger::log(instruction.log(), ERROR);
            return ErrorCode::InternalInconsistency;
        }
    }

    // Get the final Manhattan distance and print it
    uint32_t distance = ship.getManhattanDistance();
    Logger::log("Final Manhattan distance of the ship is: " +
                    std::to_string(distance),
                INFO);
    result = distance;
    return Ok;
}

ErrorCode Ship::applyInstruction(const Instruction &instruction)
{
    // Decide depending on the instruction action
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
        viewAngle = ((viewAngle + instruction.value) % 360 + 360) % 360;
        if (std::find(possibleViewValues.begin(), possibleViewValues.end(),
                      viewAngle) == possibleViewValues.end())
        {
            Logger::log("View angles does not contain a good value" +
                            std::to_string(viewAngle),
                        ERROR);
            return InternalInconsistency;
        }
    }
    else if (instruction.action == 'R')
    {
        viewAngle = ((viewAngle - instruction.value) % 360 + 360) % 360;
        if (std::find(possibleViewValues.begin(), possibleViewValues.end(),
                      viewAngle) == possibleViewValues.end())
        {
            Logger::log("View angles does not contain a good value : " +
                            std::to_string(viewAngle),
                        ERROR);
            return InternalInconsistency;
        }
    }
    else if (instruction.action == 'F')
    {
        if (viewAngle == 0)
        {
            applyInstruction(Instruction('E', instruction.value));
        }
        else if (viewAngle == 90)
        {
            applyInstruction(Instruction('N', instruction.value));
        }
        else if (viewAngle == 180)
        {
            applyInstruction(Instruction('W', instruction.value));
        }
        else if (viewAngle == 270)
        {
            applyInstruction(Instruction('S', instruction.value));
        }
        else
        {
            Logger::log("View angle value not valid", ERROR);
            return InternalInconsistency;
        }
    }
    else
    {
        Logger::log("Instruction action not recognised", ERROR);
        return InternalInconsistency;
    }

    return Ok;
}

} // namespace day12