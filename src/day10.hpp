#include <string>
#include <vector>

#include "errorCode.hpp"

class Day10
{
public:
	static ErrorCode execute(const std::string &filename, unsigned long &result1,
							 unsigned long &result2);

private:
	static ErrorCode checkAndCount(const std::vector<int> &values, unsigned long &result);
	static int countFromTo(const std::vector<int>::const_iterator &begin,
						   const std::vector<int>::const_iterator &end);
	static ErrorCode numCombinations(const std::vector<int> &values,
									 unsigned long &result);
};