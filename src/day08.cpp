#include <vector>
#include <string>

#include "day08.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

ErrorCode Day08::execute(const std::string& filename, int& result1, int& result2)
{
	// Load the strings in the input file.
	std::vector<std::string> code;
	if (FileOpener::loadVector(code, filename) != Ok)
	{
		Logger::log("Could not open file with rules", ERROR);
		return InvalidFile;
	}

	// Parse the input strings into a vector of instructions.
	std::vector<Instruction> instructions;
	if (parseIntoInstructions(instructions, code) != Ok)
	{
		Logger::log("Could not parse the code into instructions", ERROR);
		return InvalidFile;
	}
	Logger::log("Input file has been parsed into instructions", INFO);

	// Execute the instructions and get the accumulator value
	// when an instruction is executed twice.
	bool exitOK;
	if (executeInstructions(instructions, exitOK, result1) != Ok)
	{
		Logger::log("Could not execute instructions", ERROR);
		return InternalInconsistency;
	}

	// Log the result of part 1.
	Logger::log("Accumulator value when infinite loop is found: "
		+ std::to_string(result1), INFO);

	// For the second part, go through all the instructions, change them
	// and check if the program terminates.
	if (findTermination(instructions, result2) != Ok)
	{
		Logger::log("Could not find a case in which the program terminates", ERROR);
		return NoSolution;
	}

	// Log result of part two.
	Logger::log("Accumulator value when program terminates: "
		+ std::to_string(result2), INFO);
	return Ok;
}

ErrorCode Day08::parseIntoInstructions(std::vector<Instruction>& instructions,
	const std::vector<std::string>& code)
{
	size_t div;
	for (auto line = code.begin(); line != code.end(); line++)
	{
		// Add a new element to the list.
		instructions.push_back(Instruction());

		// Get the name of the instruction.
		div = (*line).find(' ', 0);
		instructions.back().name = (*line).substr(0, div);

		// Get the value of the instruction.
		try
		{
			instructions.back().value = std::stoi((*line).substr(div + 1,
				(*line).length() - div - 1));
		}
		catch (const std::exception& e)
		{
			Logger::log("Could not get the value of an instruction", ERROR);
			return InternalInconsistency;
		}
	}

	return Ok;
}

ErrorCode Day08::executeInstructions(std::vector<Instruction>& instructions,
	bool& exitOK, int& result)
{
	// Set global variables for the execution.
	size_t counter = 0;
	int accumulator = 0;

	// Create a vector that will count the number of executions
	// of each instruction.
	std::vector<int> numExecutions(instructions.size(), 0);

	// Execute all instructions.
	while (counter >= 0 && counter < instructions.size() &&
		numExecutions[counter] == 0)
	{
		// Update the number of times this instruction has been executed.
		numExecutions[counter]++;

		if (instructions[counter].name == "acc")
		{
			accumulator += instructions[counter].value;
			counter++;
		}
		else if (instructions[counter].name == "jmp")
		{
			counter += instructions[counter].value;
		}
		else if (instructions[counter].name == "nop")
		{
			counter++;
		}
	}

	// Check if the program exited normally or found an infinite loop.
	if (counter == instructions.size())
	{
		exitOK = true;
	}
	else if (numExecutions[counter] != 0)
	{
		exitOK = false;
	}
	else
	{
		Logger::log("The instruction counter is below zero, something", ERROR);
		Logger::log("is not right", ERROR);
		return InternalInconsistency;
	}

	result = accumulator;
	return Ok;
}

ErrorCode Day08::findTermination(std::vector<Instruction>& instructions,
	int& result)
{
	logInstructions(instructions);
	// Go through each of the instructions, if it is
	// a jmp, change to nop, and viceversa. Execute each time to check
	// if the program terminates.
	bool exitOK = false;
	int auxResult;
	for (auto i = instructions.begin(); i != instructions.end(); i++)
	{
		if ((*i).name == "acc")
		{
			continue;
		}
		else if ((*i).name == "jmp")
		{
			(*i).name = "nop";
		}
		else if ((*i).name == "nop")
		{
			(*i).name = "jmp";
		}
		else
		{
			Logger::log("Instruction name is not valid", ERROR);
			return InternalInconsistency;
		}

		// In the cases we are here, execute the new instructions.
		logInstructions(instructions);
		if (executeInstructions(instructions, exitOK, auxResult) != Ok)
		{
			Logger::log("Could not execute a modified program", ERROR);
			return InternalInconsistency;
		}

		// Check if program terminated.
		if (exitOK)
		{
			result = auxResult;
			return Ok;
		}

		Logger::log("hey", INFO);
		// Revert back the instructions that have been modified.
		(*i).name = (*i).name == "jmp" ? "nop" : "jmp";
		logInstructions(instructions);
	}

	Logger::log("No termination combination found", ERROR);
	return NoSolution;
}

ErrorCode Day08::logInstructions(const std::vector<Instruction>& instructions)
{
	Logger::log("Program instructions:", DEBUG);
	for (auto i = instructions.begin(); i != instructions.end(); i++)
	{
		Logger::log("\t " + (*i).name + " " + std::to_string((*i).value), DEBUG);
	}
	return Ok;
}