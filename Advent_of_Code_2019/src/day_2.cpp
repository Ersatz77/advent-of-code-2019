#include "pch.h"

std::vector<int> day_2_read_file(const std::string& path)
{
	std::ifstream file;
	file.open(path);

	// Throw exception if file is not open
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file!");
	}

	// Read all lines from file and store them in a vector
	std::vector<int> data;
	for (int line = 0; file >> line; )
	{
		data.push_back(line);
	}

	// Close file and return
	file.close();
	return data;

}

int parse(std::vector<int> intcode, const int& input_1, const int& input_2)
{
	// Override vales at index 1 and 2 because they're input values
	intcode[1] = input_1;
	intcode[2] = input_2;

	// Parse intcode
	for (int i = 0; intcode[i] != 99; i += 4)
	{
		int first_value = intcode[intcode[i + 1]];
		int second_value = intcode[intcode[i + 2]];
		int output_index = intcode[i + 3];

		// Handle opcodes
		switch (intcode[i])
		{
			// Add
			case 1:
				intcode[output_index] = first_value + second_value;
				break;
			// Multiply
			case 2:
				intcode[output_index] = first_value * second_value;
				break;
		}
	}

	// Return output value at index 0
	return intcode[0];
}

void day_2()
{
	// Read file
	std::vector<int> input = day_2_read_file("C:\\Users\\Ersatz\\source\\repos\\Advent_of_Code_2019\\Advent_of_Code_2019\\src\\inputs\\day_2.txt");;

	// Part 1
	std::cout << "Part 1 output: " << parse(input, 12, 2) << '\n';

	// Part 2
	constexpr int output = 19690720;
	int noun_verb_output = 0;
	for (int noun = 0; noun <= 99; ++noun)
	{
		for (int verb = 0; verb <= 99; ++verb)
		{
			if (parse(input, noun, verb) == output)
			{
				noun_verb_output = 100 * noun + verb;
				break;
			}
		}
	}

	std::cout << "Part 2 output: " << noun_verb_output << '\n';
}