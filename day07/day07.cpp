#include <string>
#include <vector>
#include <map>

#include "day07.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

ErrorCode Day07::execute(const std::string& filename, int& result1,
	int& result2)
{
	// Load the strings in the input file.
	std::vector<std::string> rules;
	if (FileOpener::loadVector(rules, filename) != Ok)
	{
		Logger::log("Could not open file with rules", ERROR);
		return InvalidFile;
	}

	// Create a map of maps for the rules.
	std::map<std::string, Rule> ruleMap;
	for (auto line = rules.begin(); line != rules.end(); line++)
	{
		if (parseLine(*line, ruleMap) != Ok)
		{
			Logger::log("Could not parse at least one line", ERROR);
			return InvalidFile;
		}
	}

	// With this map, find out the number of elements that have the shiny gold bag
	// as their child.
	std::set<std::string> possible;
	result1 = numBagsThanCanContain("shiny gold", ruleMap, possible);
	result2 = numBagsContainedBy("shiny gold", ruleMap);
	Logger::log("Number of bags that can ultimately contain shiny gold bag: "
		+ std::to_string(result1), INFO);
	Logger::log("Number of bags contained in a shiny gold bag: "
		+ std::to_string(result2), INFO);
	return Ok;
}

ErrorCode Day07::parseLine(const std::string& line, std::map<std::string, Rule>& ruleMap)
{
	// Get the name of the bag in this set of rules.
	std::string bagName;
	if (nextTwoWords(bagName, line, 0) != Ok)
	{
		Logger::log("Could not extract name of the bag", ERROR);
		return InternalInconsistency;
	}
	ruleMap.insert({bagName, {}});

	// Get to the point where the list begins, or find out there is no rule.
	size_t numberPos;
	if ((numberPos = line.find_first_of("0123456789", 0)) != std::string::npos)
	{
		// A digit was found, a list of bags is expected.
		if (parseList(ruleMap[bagName], line.substr(numberPos, line.length() - numberPos)) != Ok)
		{
			Logger::log("Could not parse the rules for at least one bag", ERROR);
			return Error;
		}
	}

	return Ok;
}

ErrorCode Day07::parseList(Rule& rule, const std::string& list)
{
	size_t beg = 0, end;
	short number;
	std::string name;
	while ((end = list.find_first_of(",.", beg)) != std::string::npos)
	{
		// Extract the number of the rule.
		try
		{
			number = std::stoi(list.substr(beg, list.find(' ', beg)));
		}
		catch (const std::exception& e)
		{
			Logger::log("Could not extract the number of a rule", ERROR);
			return InternalInconsistency;
		}
		
		// Extract the name of the bag.
		if (nextTwoWords(name, list, list.find(' ', beg) + 1) != Ok)
		{
			Logger::log("Could not extract name of a bag in rule", ERROR);
			return InternalInconsistency;
		}

		// Insert the rule in the current map.
		rule.insert({name, number});

		// Update the beg and end counters.
		beg = end + 2;
	}

	return Ok;
}

ErrorCode Day07::nextTwoWords(std::string& output, const std::string& input, const size_t beg)
{
	size_t end = input.find(' ', input.find(' ', beg) + 1);
	output = input.substr(beg, end - beg);
	return Ok;
}

int Day07::numBagsThanCanContain(const std::string& name,
	const std::map<std::string, Rule>& map, std::set<std::string>& possible)
{
	int result = 0;
	for (auto i = map.begin(); i != map.end(); i++)
	{
		if ((*i).second.find(name) != (*i).second.end())
		{
			// If this bag has not yet been found, add 1 to the possibilities.
			if (possible.insert((*i).first).second)
			{
				result++;
			}

			// Check the possibilities of this bag.
			result += numBagsThanCanContain((*i).first, map, possible);
		}
	}

	return result;
}

int Day07::numBagsContainedBy(const std::string& name,
	const std::map<std::string, Rule>& map)
{
	// Find the rule for the bag provided.
	Rule rule = map.at(name);

	// If this bag has no rules, it does not
	// need to contain bags.
	if (rule.empty())
	{
		return 0;
	}

	// For each of the bags in the rule, count the recursive number
	// of bags inside it.
	int result = 0;
	for (auto i = rule.begin(); i != rule.end(); i++)
	{
		result += (*i).second * (numBagsContainedBy((*i).first, map) + 1);
	}

	return result;
}