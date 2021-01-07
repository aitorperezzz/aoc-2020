#include <string>
#include <vector>

#include "errorCode.hpp"

class Day10
{
public:
	static ErrorCode execute(const std::string& filename, int& result1,
		int& result2);

private:
	static ErrorCode checkAndCount(const std::vector<int>& values, int& result);
	static int countFromTo(const std::vector<int>::const_iterator& begin,
		const std::vector<int>::const_iterator& end);
	static ErrorCode numArrangements(const std::vector<int>& values,
		int& result);
};