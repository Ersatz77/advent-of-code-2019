#include "pch.h"
#include "utility/intcode.h"

void day_9()
{
	std::vector<long long> input = intcode::convert_to_intcode("C:\\Users\\Ersatz\\source\\repos\\Advent_of_Code_2019\\Advent_of_Code_2019\\src\\inputs\\day_9.txt", SHRT_MAX);
	intcode::parse(input);
	std::cout << '\n';
}