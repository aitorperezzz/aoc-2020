#pragma once

#include <string>
#include <vector>

#include "errorCode.hpp"

struct Instruction
{
	std::string name; // name of the instruction
	int value; // right value of the instruction (positive or negative integer)
};

class Day08
{
public:
	static ErrorCode execute(const std::string& filename, int& result1,
		int& result2);

private:
	static ErrorCode parseIntoInstructions(std::vector<Instruction>& instructions,
		const std::vector<std::string>& code);
	static ErrorCode executeInstructions(std::vector<Instruction>& instructions,
		bool& exitOK, int& result);
	static ErrorCode findTermination(std::vector<Instruction>& instructions,
		int& result);
	static ErrorCode logInstructions(const std::vector<Instruction>& instructions);
};