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
    std::map<unsigned long, unsigned long> memory;
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
    virtual ~Instruction() = default;
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
    unsigned long address;
    std::bitset<BIT_LENGTH> value;
    ErrorCode execute(const Version version, Program &program) const;
    void log() const;
    ErrorCode applyPossibilities(const unsigned long address,
                                 const unsigned long value,
                                 const std::deque<size_t> &floatingIndices,
                                 Program &program) const;
};

/// @brief Returns the results for the day
ErrorCode execute(const std::string &filename, const Version version,
                  unsigned long &result);

} // namespace day14