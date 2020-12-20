#include "day01.hpp"

int main(void)
{
	int result;
	if (Day01::executePartOne("./input/input.txt", result) != Ok)
	{
		return -1;
	}

	if (Day01::executePartTwo("./input/input.txt", result) != Ok)
	{
		return -1;
	}

	return 0;
}