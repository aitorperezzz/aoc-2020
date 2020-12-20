#include "day09.hpp"

int main(void)
{
	unsigned long result1, result2;
	if (Day09::execute("./input/input.txt", 25, result1, result2) != Ok)
	{
		return -1;
	}
	return 0;
}