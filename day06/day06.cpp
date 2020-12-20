#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <algorithm>

#include "day06.hpp"
#include "fileOpener.hpp"
#include "logger.hpp"

ErrorCode Day06::execute(const std::string& filename, short& result1,
	short& result2)
{
	// Load the strings in the input file.
	std::vector<std::string> responses;
	if (FileOpener::loadVector(responses, filename) != Ok)
	{
		Logger::log("Could not open file with responses", ERROR);
		return InvalidFile;
	}

	// Create a vector that will store all the info related to all group's
	// responses. Each element of the vector is a GroupInfo, with all the 
	// response lines, and the set of letter to which everyone and anyone
	// answered yes.
	std::vector<GroupInfo> infos;
	infos.push_back(GroupInfo());

	// Create variables that will store the accumulated counts.
	short anyoneCount = 0, everyoneCount = 0;
	for (size_t i = 0, n = responses.size(); i < n; i++)
	{
		// Put this line of responses in the last group info.
		if (responses[i].size() != 0)
		{
			infos.back().responses.push_back({});
			for (size_t j = 0; j < responses[i].size(); j++)
			{
				infos.back().responses.back().insert(responses[i][j]);
			}
		}

		// If this is a blank line or the final row in the input file.
		if (responses[i] == "" || i == responses.size() - 1)
		{
			// Parse the group info.
			if (parseGroupInfo(infos.back()) != Ok)
			{
				Logger::log("Could not parse group info", ERROR);
				return InternalInconsistency;
			}

			// Update the counts.
			debugGroupInfo(infos.back());
			anyoneCount += infos.back().anyoneYes.size();
			everyoneCount += infos.back().everyoneYes.size();
			infos.push_back(GroupInfo());
		}
	}

	// Show and store results.
	Logger::log("Count of questions with anyone answering yes: " +
		std::to_string(anyoneCount), INFO);
	Logger::log("Count of questions with everyone answering yes: " +
		std::to_string(everyoneCount), INFO);
	result1 = anyoneCount;
	result2 = everyoneCount;
	return Ok;
}

void Day06::debugGroupInfo(const GroupInfo& info)
{
	std::cout << "Anyone: ";
	for (auto i = info.anyoneYes.begin(); i != info.anyoneYes.end(); i++)
	{
		std::cout << (*i);
	}
	std::cout <<  " [" << info.anyoneYes.size() << "]; ";

	std::cout << "Everyone: ";
	for (auto i = info.everyoneYes.begin(); i != info.everyoneYes.end(); i++)
	{
		std::cout << (*i);
	}
	std::cout <<  " [" << info.everyoneYes.size() << "]" << std::endl;
}

ErrorCode Day06::parseGroupInfo(GroupInfo& info)
{
	// Initialize the anyone and everyone sets.
	std::copy(info.responses[0].begin(), info.responses[0].end(),
		std::inserter(info.anyoneYes, info.anyoneYes.begin()));
	std::copy(info.responses[0].begin(), info.responses[0].end(),
		std::inserter(info.everyoneYes, info.everyoneYes.begin()));

	// For the rest of line sets, beginning at index 1, find intersection
	// and union of the current line set with the anyone and everyone sets.
	std::set<char> auxIntersection, auxUnion;
	for (auto line = info.responses.begin() + 1; line != info.responses.end(); line++)
	{
		// Update union and intersection sets.
		auxUnion.clear();
		auxIntersection.clear();
		std::set_union(info.anyoneYes.begin(), info.anyoneYes.end(),
			(*line).begin(), (*line).end(), std::inserter(auxUnion, auxUnion.begin()));
		std::set_intersection(info.everyoneYes.begin(), info.everyoneYes.end(),
			(*line).begin(), (*line).end(), std::inserter(auxIntersection, auxIntersection.begin()));
		
		// Copy variables.
		info.anyoneYes.clear();
		info.everyoneYes.clear();
		info.anyoneYes.insert(auxUnion.begin(), auxUnion.end());
		info.everyoneYes.insert(auxIntersection.begin(), auxIntersection.end());
	}

	return Ok;
}