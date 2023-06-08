#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

#include "day18.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

namespace day18
{

// Return the index of the parenthesis that closes the current open one
size_t findParenthesisClose(const std::string &operation,
                            const size_t parenthesisOpen)
{
    // In the beginning, we just need to find one closing parenthesis
    int findClosing = 1;

    // Go through the operation string
    for (size_t i = parenthesisOpen + 1; i < operation.length(); i++)
    {
        if (operation[i] == '(')
        {
            findClosing++;
        }
        if (operation[i] == ')')
        {
            findClosing--;
        }

        // If we do not need to find more closing parenthesis, return
        if (findClosing == 0)
        {
            return i;
        }
    }

    // No closing parenthesis has been found, something is very wrong
    throw std::invalid_argument("Could not find closing parenthesis");
}

// Return the index of the operator that has the highest precedence depending
// on the type of math
size_t getNextOperatorPosition(const std::string &operation, const Math math)
{
    if (math == Math::Basic)
    {
        return operation.find_first_of("+*");
    }
    else
    {
        size_t operatorPos = operation.find('+');
        if (operatorPos == std::string::npos)
        {
            return operation.find('*');
        }
        else
        {
            return operatorPos;
        }
    }
}

// Computes an operation with a string that contains no parenthesis.
// In this case, only digits and operators are present
std::string computeWithNoParenthesis(const std::string operation,
                                     const Math math)
{
    std::string currentOperation = operation;
    size_t operatorPos;

    // Look ahead for the position of the operator that has the highest
    // precedence
    while ((operatorPos = getNextOperatorPosition(currentOperation, math)) !=
           std::string::npos)
    {
        // Get the index of the start of the number that is closest to the
        // operator, to its left
        size_t begin;
        for (size_t i = operatorPos - 1; i >= 0; i--)
        {
            if (!std::isdigit(currentOperation[i]))
            {
                begin = i + 1;
                break;
            }
            if (i == 0)
            {
                begin = 0;
            }
        }
        // Create the number to the left of the operator
        int64_t firstNumber =
            std::stol(currentOperation.substr(begin, operatorPos - begin));

        // Get the index of the end of the number closest to the operator, to
        // the right
        size_t end;
        for (size_t i = operatorPos + 1; i < currentOperation.length(); i++)
        {
            if (!std::isdigit(currentOperation[i]))
            {
                end = i - 1;
                break;
            }
            if (i == currentOperation.length() - 1)
            {
                end = currentOperation.length() - 1;
            }
        }
        // Convert the section of string to a number
        int64_t secondNumber = std::stol(
            currentOperation.substr(operatorPos + 1, end - operatorPos));

        int64_t result;
        if (currentOperation[operatorPos] == '+')
        {
            result = firstNumber + secondNumber;
        }
        else if (currentOperation[operatorPos] == '*')
        {
            result = firstNumber * secondNumber;
        }
        else
        {
            throw std::invalid_argument("Operator not recognised");
        }

        // Overwrite the operation with the result just computed
        currentOperation =
            currentOperation.substr(0, begin) + std::to_string(result) +
            currentOperation.substr(end + 1, currentOperation.length() - end);
    }

    return currentOperation;
}

std::string compute(const std::string &operation, const Math math)
{
    // Trim the operation received by removing all the spaces
    std::string trimmedOperation = operation;
    trimmedOperation.erase(
        std::remove(trimmedOperation.begin(), trimmedOperation.end(), ' '),
        trimmedOperation.end());

    // While there are parenthesis in the expression
    size_t parenthesisOpen;
    while ((parenthesisOpen = trimmedOperation.find('(')) != std::string::npos)
    {
        // Find where the parenthesis close
        size_t parenthesisClose =
            findParenthesisClose(trimmedOperation, parenthesisOpen);

        // Get the result of the operation between parenthesis
        std::string result = compute(
            trimmedOperation.substr(parenthesisOpen + 1,
                                    parenthesisClose - parenthesisOpen - 1),
            math);

        // Overwrite the space between parenthesis with the new result
        trimmedOperation = trimmedOperation.substr(0, parenthesisOpen) +
                           result +
                           trimmedOperation.substr(parenthesisClose + 1,
                                                   trimmedOperation.length() -
                                                       parenthesisClose - 1);
    }

    // Compute an expression that does not contain parenthesis
    return computeWithNoParenthesis(trimmedOperation, math);
}

ErrorCode execute(const std::string &filename, int64_t &result1,
                  int64_t &result2)
{
    // Load input
    std::vector<std::string> input;
    if (FileOpener::loadVector(input, filename) != Ok)
    {
        Logger::log("Could not read values from file", ERROR);
        throw std::invalid_argument("");
    }

    // Compute the result of each line and sum all of them together
    int64_t totalResultBasic = 0, totalResultAdvanced = 0;
    for (auto &line : input)
    {
        totalResultBasic += std::stol(compute(line, Math::Basic));
        totalResultAdvanced += std::stol(compute(line, Math::Advanced));
    }

    Logger::log("Result with basic math: " + std::to_string(totalResultBasic),
                INFO);
    result1 = totalResultBasic;
    Logger::log("Result with advanced math: " +
                    std::to_string(totalResultAdvanced),
                INFO);
    result2 = totalResultAdvanced;

    return ErrorCode::Ok;
}
} // namespace day18