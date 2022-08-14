#pragma once

#include <bitset>
#include <deque>
#include <memory>
#include <string>
#include <vector>

#include "errorCode.hpp"

namespace day14
{

/// Define the length, in bits, of a mask
constexpr size_t BIT_LENGTH = 36;

enum Version
{
    ONE,
    TWO
};

class Instruction;

struct Program
{
    std::vector<std::unique_ptr<Instruction>> instructions;
    std::map<uint64_t, uint64_t> memory;
    std::array<int, BIT_LENGTH> mask;

    Program(const std::vector<std::string> &lines);

    ErrorCode execute(const Version version);
};

class Instruction
{
public:
    virtual ErrorCode execute(const Version version,
                              Program &program) const = 0;
    virtual void log() const = 0;
};

class MaskInstruction : public Instruction
{
public:
    std::array<int, BIT_LENGTH> mask;
    ErrorCode execute(const Version version, Program &program) const;
    void log() const;
};

class StoreInstruction : public Instruction
{
public:
    uint64_t address;
    std::bitset<BIT_LENGTH> value;
    ErrorCode execute(const Version version, Program &program) const;
    void log() const;
    ErrorCode applyPossibilities(const uint64_t address, const uint64_t value,
                                 const std::deque<size_t> &floatingIndices,
                                 Program &program) const;
};

/// @brief Returns the results for the day
ErrorCode execute(const std::string &filename, const Version version,
                  uint64_t &result);

} // namespace day14