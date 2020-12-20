#pragma once

#include <string>
#include <vector>
#include <set>

#include "errorCode.hpp"

struct GroupInfo
{
	// Response lines from all members of the group.
	std::vector<std::set<char>> responses;

	// Set with all the letters to which at least one person in
	// the group has answered yes.
	std::set<char> anyoneYes;

	// Set with all the letters to which everyone answered yes.
	std::set<char> everyoneYes;
};

class Day06
{
public:
	static ErrorCode execute(const std::string& filename,
		short& result1, short& result2);
	static void debugGroupInfo(const GroupInfo& info);
	static ErrorCode parseGroupInfo(GroupInfo& info);
};