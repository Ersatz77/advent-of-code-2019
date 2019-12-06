#include "pch.h"
#pragma warning (disable : 26451)

// Read file and return contents in an int vector
std::vector<int> day_5_read_file(const std::string& path)
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

void parse(std::vector<int> intcode)
{
	// Parse intcode
	for (int i = 0; intcode[i] != 99; )
	{
		// Get opcode, operation, and the mode for each parameter
		std::string opcode = std::to_string(intcode[i]);
		opcode.insert(0, 5 - opcode.length(), '0');

		int operation = std::stoi(opcode.substr(3, 2));

		int parameter_1_mode = opcode[2] - int('0');
		int parameter_2_mode = opcode[1] - int('0');
		int parameter_3_mode = opcode[0] - int('0');

		// Handle opcodes
		switch (operation)
		{
			// Add
			case 1:
			{
				int argument_1 = (parameter_1_mode == 1) ? intcode[i + 1] : intcode[intcode[i + 1]];
				int argument_2 = (parameter_2_mode == 1) ? intcode[i + 2] : intcode[intcode[i + 2]];
				intcode[intcode[i + 3]] = argument_1 + argument_2;
				i += 4;
				break;
			}

			// Multiply
			case 2:
			{
				int argument_1 = (parameter_1_mode == 1) ? intcode[i + 1] : intcode[intcode[i + 1]];
				int argument_2 = (parameter_2_mode == 1) ? intcode[i + 2] : intcode[intcode[i + 2]];
				intcode[intcode[i + 3]] = argument_1 * argument_2;
				i += 4;
				break;
			}

			// Input
			case 3:
			{
				int input = 0;
				std::cout << "Input: ";
				std::cin >> input;
				std::cout << '\n';

				intcode[intcode[i + 1]] = input;
				i += 2;
				break;
			}

			// Output
			case 4:
			{
				std::cout << "Value at position " << intcode[i + 1] << ": " << std::to_string(intcode[intcode[i + 1]]) << '\n';
				i += 2;
				break;
			}

			// Jump if true
			case 5:
			{
				int argument_1 = (parameter_1_mode == 1) ? intcode[i + 1] : intcode[intcode[i + 1]];
				int argument_2 = (parameter_2_mode == 1) ? intcode[i + 2] : intcode[intcode[i + 2]];
				i = (argument_1 != 0) ? i = argument_2 : i + 3;
				break;
			}

			// Jump if false
			case 6:
			{
				int argument_1 = (parameter_1_mode == 1) ? intcode[i + 1] : intcode[intcode[i + 1]];
				int argument_2 = (parameter_2_mode == 1) ? intcode[i + 2] : intcode[intcode[i + 2]];
				i = (argument_1 == 0) ? i = argument_2 : i + 3;
				break;
			}

			// Less than
			case 7:
			{
				int argument_1 = (parameter_1_mode == 1) ? intcode[i + 1] : intcode[intcode[i + 1]];
				int argument_2 = (parameter_2_mode == 1) ? intcode[i + 2] : intcode[intcode[i + 2]];
				intcode[intcode[i + 3]] = (argument_1 < argument_2) ? 1 : 0;
				i += 4;
				break;
			}

			// Equals
			case 8:
			{
				int argument_1 = (parameter_1_mode == 1) ? intcode[i + 1] : intcode[intcode[i + 1]];
				int argument_2 = (parameter_2_mode == 1) ? intcode[i + 2] : intcode[intcode[i + 2]];
				intcode[intcode[i + 3]] = (argument_1 == argument_2) ? 1 : 0;
				i += 4;
				break;
			}
		}
	}
}

void day_5()
{
	// Read file
	std::vector<int> input = day_5_read_file("C:\\Users\\Ersatz\\source\\repos\\Advent_of_Code_2019\\Advent_of_Code_2019\\src\\inputs\\day_5.txt");

	parse(input);
	std::cout << '\n';
}