#pragma once

#include <string>
#include <vector>

#include "errorCode.hpp"

namespace day16
{

struct Rule
{
    std::array<std::pair<int, int>, 2> ranges;

    /// @brief Creates a rule out of a line
    Rule(const std::string &line);

    /// Decides if the number is not valid for any of the fields
    bool isInvalid(const int number) const;
};

class Document
{
public:
    // Numbers on my ticket
    std::vector<int> myTicket;

    /// @brief Create a document out of a file
    /// @param filename Name of the input file
    Document(const std::string &filename);

    /// @brief Returns the scanning error rate for all nearby tickets
    /// @param purge Removes the invalid nearby tickets from the document on the
    /// fly
    int getScanningErrorRate(const bool purge);

    /// @brief Out of a document, extract the correct order of the fields such
    /// that the order is valid for all valid tickets
    /// @return List of field names in their correct order
    std::vector<std::string> extractCorrectOrder();

private:
    // Rules that are found at the beginning of the ticket
    std::map<std::string, Rule> rules;

    // Numbers of all the nearby tickets
    std::vector<std::vector<int>> nearbyTickets;

    /// @brief Parses a line, returning the numbers of a ticket
    std::vector<int> parseTicket(const std::string &line);

    /// @brief Extract all the rules that apply. For each of the numbers in the
    /// ticket, extract the list of rule names that apply to that position
    std::vector<std::vector<std::string>> extractRulesThatApply(
        const std::vector<int> &ticket);

    /// @brief Global rules gets updated by removing all rules there that do not
    /// intersect with the rules given in the current ticket
    /// @param ticketRules Rules of the current ticket
    /// @param globalRules Rules that apply to the complete set of tickets
    /// currently
    void mergeRules(const std::vector<std::vector<std::string>> &ticketRules,
                    std::vector<std::vector<std::string>> &globalRules);
};

/// @brief Returns the results for the day
ErrorCode execute(const std::string &filename, int &scanningErrorRate,
                  int64_t &finalProduct);

} // namespace day16