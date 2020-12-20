#include "day03.hpp"

int main(void)
{
	int result1;
	unsigned long result2;
	if (Day03::execute("./input/input.txt", result1, result2) != Ok)
	{
		return -1;
	}

	return 0;
}