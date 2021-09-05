#pragma once

#include <string>
#include <map>
#include <set>

#include "errorCode.hpp"

#define Rule std::map<std::string, int>

class Day07
{
public:
	static ErrorCode execute(const std::string& filename,
		int& result1, int& result2);
	
	static ErrorCode parseLine(const std::string& line,
		std::map<std::string, Rule>& ruleMap);
	static ErrorCode parseList(Rule& rule, const std::string& list);
	static ErrorCode nextTwoWords(std::string& output, const std::string& input,
		const size_t beg);
	
	static int numBagsThanCanContain(const std::string& name,
		const std::map<std::string, Rule>& map, std::set<std::string>& possible);
	
	static int numBagsContainedBy(const std::string& name,
		const std::map<std::string, Rule>& map);
};