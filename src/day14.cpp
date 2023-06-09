#include <bitset>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>

#include "day14.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

namespace day14
{

Program::Program(const std::vector<std::string> &lines)
{
    for (const auto &line : lines)
    {
        // Find a possible [ character in the string
        size_t firstBracket = line.find('[');
        if (firstBracket != std::string::npos)
        {
            // This is a store instruction, grab the value between the []
            size_t secondBracket = line.substr(firstBracket).find('[');

            std::string addressString =
                line.substr(firstBracket + 1, secondBracket - firstBracket - 1);
            unsigned long address = std::stoul(addressString);

            // Grab the = sign
            size_t equalSign = line.find('=');
            equalSign += 2;
            std::string valueString = line.substr(equalSign);
            unsigned long value = std::stoul(valueString);

            // Create instruction
            StoreInstruction instruction;
            instruction.address = address;
            instruction.value = value;
            instructions.push_back(
                std::make_unique<StoreInstruction>(instruction));
        }
        else
        {
            // This is a mask instruction
            // Grab the = sign
            size_t equalSign = line.find('=');
            equalSign += 2;
            std::string valueString = line.substr(equalSign);

            if (valueString.length() != BIT_LENGTH)
            {
                throw std::invalid_argument(
                    "String that stores the supposed mask does not have "
                    "length 36");
            }

            // Create a mask with the above string
            std::array<int, BIT_LENGTH> mask;
            for (int i = BIT_LENGTH - 1; i >= 0; i--)
            {
                if (valueString[i] == 'X')
                {
                    mask[BIT_LENGTH - 1 - i] = -1;
                }
                else
                {
                    mask[BIT_LENGTH - 1 - i] =
                        std::stoi(valueString.substr(i, 1));
                }
            }

            // Create a mask instruction and add it to the current ones
            MaskInstruction instruction;
            instruction.mask = mask;
            instructions.push_back(
                std::make_unique<MaskInstruction>(instruction));
        }
    }
}

ErrorCode Program::execute(const Version version)
{
    // Call execute on each of the instructions
    for (const auto &instruction : instructions)
    {
        instruction->log();
        if (instruction->execute(version, *this) != ErrorCode::Ok)
        {
            Logger::log("Instruction could not execute", ERROR);
            return ErrorCode::InternalInconsistency;
        }
    }

    return ErrorCode::Ok;
}

ErrorCode MaskInstruction::execute(const Version version,
                                   Program &program) const
{
    (void)version;
    program.mask = mask;
    return ErrorCode::Ok;
}

void MaskInstruction::log() const
{
    std::stringstream message;
    std::string maskString;
    for (size_t i = 0; i < BIT_LENGTH; i++)
    {
        if (mask[i] == -1)
        {
            maskString += "X";
        }
        else
        {
            maskString += std::to_string(mask[i]);
        }
    }
    std::reverse(maskString.begin(), maskString.end());
    message << "Mask instruction: setting mask to " << maskString;
    Logger::log(message.str(), INFO);
}

ErrorCode StoreInstruction::execute(const Version version,
                                    Program &program) const
{
    if (version == ONE)
    {
        // First update value according to the current program's mask
        std::bitset<BIT_LENGTH> auxValue = value;
        for (size_t i = 0; i < BIT_LENGTH; i++)
        {
            switch (program.mask[i])
            {
            case -1:
                // leave the value alone
                break;
            case 0:
            case 1:
                auxValue[i] = program.mask[i];
                break;

            default:
                Logger::log("Mask bit value not understood: " +
                                std::to_string(program.mask[i]),
                            ERROR);
                return ErrorCode::InternalInconsistency;
            }
        }

        // Update the value at the requested address
        program.memory[address] =
            static_cast<unsigned long>(auxValue.to_ulong());
        return ErrorCode::Ok;
    }
    else
    {
        // First parse the values in the mask that are fixed and get a vector
        // with all the positions on which the mask is floating
        unsigned long auxAddress = address;
        std::deque<size_t> floatingIndices;
        for (size_t i = 0; i < BIT_LENGTH; i++)
        {
            if (program.mask[i] == 1)
            {
                // Overwrite the bit with a 1
                auxAddress |= (1ull << i);
            }
            else if (program.mask[i] == -1)
            {
                // This is a floating index
                floatingIndices.push_back(i);
            }
        }

        // Apply all the possible values
        applyPossibilities(auxAddress, value.to_ullong(), floatingIndices,
                           program);
        return ErrorCode::Ok;
    }
}

ErrorCode StoreInstruction::applyPossibilities(
    const unsigned long address, const unsigned long value,
    const std::deque<size_t> &floatingIndices, Program &program) const
{
    if (floatingIndices.size() == 0)
    {
        // Then the value should be taken as it is
        program.memory[address] = value;
    }
    else
    {
        // Apply the possibilities in the first floating index
        unsigned long address1 = address | (1ull << floatingIndices.front());
        unsigned long address2 = address & ~(1ull << floatingIndices.front());

        // Remove from the deque the first element, and then call recursively
        auto auxFloatingIndices = floatingIndices;
        auxFloatingIndices.pop_front();
        applyPossibilities(address1, value, auxFloatingIndices, program);
        applyPossibilities(address2, value, auxFloatingIndices, program);
    }

    return ErrorCode::Ok;
}

void StoreInstruction::log() const
{
    std::stringstream message;
    message << "Store instruction: Memory[" << address << "] = " << value;
    Logger::log(message.str(), INFO);
}

ErrorCode execute(const std::string &filename, const Version version,
                  unsigned long &result)
{
    // Load input
    std::vector<std::string> lines;
    if (FileOpener::loadVector(lines, filename) != Ok)
    {
        Logger::log("Could not read values from file", ERROR);
        return InvalidFile;
    }

    // Create program from the input lines
    Program program(lines);

    // Execute program
    Logger::log("Executing with version " + std::to_string(version + 1), INFO);
    program.execute(version);

    // Sum the values in memory
    result = 0;
    for (const auto &x : program.memory)
    {
        result += x.second;
    }
    Logger::log("Result: " + std::to_string(result), INFO);
    return ErrorCode::Ok;
}

} // namespace day14