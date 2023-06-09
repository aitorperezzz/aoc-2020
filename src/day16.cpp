#include <iostream>
#include <map>
#include <numeric>
#include <sstream>

#include "day16.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

namespace day16
{

Rule::Rule(const std::string &line)
{
    // Get past the colon
    int rangeBegin = line.find(':');
    if ((size_t)rangeBegin == std::string::npos)
    {
        throw std::invalid_argument(
            "Lines provided to Rules constructor do not have the "
            "proper format: " +
            line);
    }
    rangeBegin += 2;

    // Find the space after the colon, which ends the range

    // Get the first range
    int rangeLen = line.substr(rangeBegin).find(' ');
    std::string range = line.substr(rangeBegin, rangeLen);
    int dash = range.find('-');
    ranges[0] = std::make_pair(
        std::stoi(range.substr(0, dash)),
        std::stoi(range.substr(dash + 1, range.length() - dash - 1)));

    // Get the second range
    rangeBegin = rangeBegin + rangeLen + 4;
    range = line.substr(rangeBegin);
    dash = range.find('-');
    ranges[1] = std::make_pair(
        std::stoi(range.substr(0, dash)),
        std::stoi(range.substr(dash + 1, range.length() - dash - 1)));
}

bool Rule::isInvalid(const int number) const
{
    for (const auto &range : ranges)
    {
        if (range.first <= number && number <= range.second)
        {
            // This range is valid, so the number is not invalid
            return false;
        }
    }
    return true;
}

Document::Document(const std::string &filename)
{
    // Load input
    std::vector<std::string> lines;
    if (FileOpener::loadVector(lines, filename) != Ok)
    {
        Logger::log("Could not read values from file", ERROR);
        throw std::invalid_argument("");
    }

    // Parse the lines that will store the rules
    size_t lineNumber = 0;
    while (lines[lineNumber] != "")
    {
        // Add to the current list of rules
        std::string key =
            lines[lineNumber].substr(0, lines[lineNumber].find(':'));
        rules.emplace(key, Rule(lines[lineNumber]));
        lineNumber++;
    }

    // Sanity check
    lineNumber++;
    if (lines[lineNumber].find("your") == std::string::npos)
    {
        throw std::invalid_argument("Format problem: your has not been found");
    }

    // Parse my ticket
    lineNumber++;
    myTicket = parseTicket(lines[lineNumber]);

    // Sanity check
    lineNumber += 2;
    if (lines[lineNumber].find("nearby") == std::string::npos)
    {
        throw std::invalid_argument(
            "Format problem: nearby has not been found");
    }

    // Parse the rest of the tickets
    lineNumber++;
    while (lineNumber < lines.size())
    {
        nearbyTickets.emplace_back(parseTicket(lines[lineNumber]));
        lineNumber++;
    }
}

std::vector<int> Document::parseTicket(const std::string &line)
{
    std::vector<int> ticket;
    size_t start = 0, end = line.find(',');
    while (end != std::string::npos)
    {
        ticket.push_back(std::stoi(line.substr(start, end - start)));
        start = end + 1;
        end = line.find(',', start);
    }
    ticket.push_back(std::stoi(line.substr(start)));
    return ticket;
}

int Document::getScanningErrorRate(const bool purge)
{
    // For each number in the ticket, check if the number is invalid
    int errorRate = 0;
    size_t ticket = 0;
    while (ticket < nearbyTickets.size())
    {
        bool validTicket = true;
        for (const auto number : nearbyTickets[ticket])
        {
            bool valid = false;
            for (auto rule = rules.begin(); rule != rules.end(); rule++)
            {
                if (!rule->second.isInvalid(number))
                {
                    valid = true;
                    break;
                }
            }
            if (!valid)
            {
                errorRate += number;
                validTicket = false;
            }
        }
        if (!validTicket)
        {
            nearbyTickets.erase(nearbyTickets.begin() + ticket);
        }
        else
        {
            ticket++;
        }
    }
    return errorRate;
}

std::vector<std::vector<std::string>> Document::extractRulesThatApply(
    const std::vector<int> &ticket)
{
    std::vector<std::vector<std::string>> result;
    for (const auto number : ticket)
    {
        std::vector<std::string> currentRules;
        for (auto rule = rules.begin(); rule != rules.end(); rule++)
        {
            if (!rule->second.isInvalid(number))
            {
                currentRules.push_back(rule->first);
            }
        }
        result.push_back(std::move(currentRules));
    }

    return result;
}

void Document::mergeRules(
    const std::vector<std::vector<std::string>> &ticketRules,
    std::vector<std::vector<std::string>> &globalRules)
{
    // For each of the numbers
    for (size_t globalRuleIndex = 0; globalRuleIndex < globalRules.size();
         globalRuleIndex++)
    {
        // Loop through all the rules in the global list
        size_t rule = 0;
        while (rule < globalRules[globalRuleIndex].size())
        {
            std::string currGlobalRule = globalRules[globalRuleIndex][rule];
            bool found = false;
            for (const auto &ticketRule : ticketRules[globalRuleIndex])
            {
                if (currGlobalRule == ticketRule)
                {
                    found = true;
                    break;
                }
            }
            // Try to find the global rule inside the ticket rules
            if (!found)
            {
                // This global rule has not been found in the ticket rules,
                // so it wouldn't be valid for the ticket, so remove it
                globalRules[globalRuleIndex].erase(
                    globalRules[globalRuleIndex].begin() + rule);
            }
            else
            {
                rule++;
            }
        }
    }
}

std::vector<std::string> Document::extractCorrectOrder()
{
    // Begin with a possible ordering that has all the possibilities in each
    // position
    std::vector<std::vector<std::string>> possibilities;
    // Get the complete list of names that make up the global rules
    std::vector<std::string> ruleList;
    for (auto rule = rules.begin(); rule != rules.end(); rule++)
    {
        ruleList.push_back(rule->first);
    }
    // For each position in my ticket, add the complete list of rule names
    for (size_t i = 0; i < myTicket.size(); i++)
    {
        possibilities.push_back(ruleList);
    }

    // Loop through the nearby tickets and make the intersection
    for (const auto &ticket : nearbyTickets)
    {
        // Remove, from the current possibilities, the ones that are not
        // valid for this ticket
        mergeRules(extractRulesThatApply(ticket), possibilities);
    }
    // Now, the possibilities list has the possibilities that are valid for
    // all tickets

    // Sanity check and preparation of return value
    std::vector<std::string> result(possibilities.size());
    std::vector<size_t> pendingIndices(possibilities.size());
    std::iota(pendingIndices.begin(), pendingIndices.end(), 0);
    while (pendingIndices.size() != 0)
    {
        for (size_t i = 0; i < pendingIndices.size(); i++)
        {
            // Check if the current possibilites are just one value.
            if (possibilities[i].size() == 1)
            {
                // The key is fixed for this index
                std::string key = possibilities[i].front();
                result[pendingIndices[i]] = key;

                // Remove from pending indices
                pendingIndices.erase(pendingIndices.begin() + i);

                // Remove from possibilities
                possibilities.erase(possibilities.begin() + i);

                // Remove from the rest of possibilites
                for (auto &rules : possibilities)
                {
                    for (size_t i = 0; i < rules.size(); i++)
                    {
                        if (rules[i] == key)
                        {
                            rules.erase(rules.begin() + i);
                            break;
                        }
                    }
                }
                break;
            }
        }
    }
    for (const auto &value : possibilities)
    {
        if (value.size() != 1)
        {
            throw std::invalid_argument("More than one possibility");
        }
        result.push_back(value.front());
    }
    return result;
}

ErrorCode execute(const std::string &filename, int &scanningErrorRate,
                  long &finalProduct)
{
    // Create the reference document
    auto document = Document(filename);

    // Find the ticket scanning error rate
    scanningErrorRate = document.getScanningErrorRate(true);
    Logger::log("Ticket scanning error rate: " +
                    std::to_string(scanningErrorRate),
                INFO);

    // Out of all the remaining nearby tickets, extract the correct order
    auto correctOrder = document.extractCorrectOrder();
    std::stringstream message;
    for (const auto &field : correctOrder)
    {
        message << field << " ";
    }
    Logger::log("Correct order extracted: " + message.str(), INFO);

    // Find the product requested for part 2
    finalProduct = static_cast<long>(1);
    for (size_t index = 0; index < correctOrder.size(); index++)
    {
        if (correctOrder[index].find("departure") != std::string::npos)
        {
            finalProduct *= static_cast<long>(document.myTicket[index]);
        }
    }
    Logger::log("Product: " + std::to_string(finalProduct), INFO);
    return ErrorCode::Ok;
}

} // namespace day16