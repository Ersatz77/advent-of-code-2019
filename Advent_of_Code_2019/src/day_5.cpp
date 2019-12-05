#include "pch.h"

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
	for (unsigned int i = 0; intcode[i] != 99; )
	{
		// Get parameters from opcode
		std::string opcode = std::to_string(intcode[i]);
		opcode.insert(0, 5 - opcode.length(), '0');

		int operation = std::stoi(opcode.substr(3, 2));
		int parameter_1_mode = opcode[2] - int('0');
		int parameter_2_mode = opcode[1] - int('0');
		int parameter_3_mode = opcode[0] - int('0');

		// Get parameter positions and arguments
		// Does not respect operation length
		int parameter_1_pos = i + 1;
		int parameter_2_pos = i + 2;
		int parameter_3_pos = i + 3;

		int argument_1 = (parameter_1_mode == 1) ? intcode[parameter_1_pos] : intcode[intcode[parameter_1_pos]];
		int argument_2 = (parameter_2_mode == 1) ? intcode[parameter_2_pos] : intcode[intcode[parameter_2_pos]];

		// Handle opcodes
		switch (operation)
		{
			// Add
			case 1:
			{
				intcode[intcode[parameter_3_pos]] = argument_1 + argument_2;
				i += 4;
				break;
			}

			// Multiply
			case 2:
			{
				intcode[intcode[parameter_3_pos]] = argument_1 * argument_2;
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

				intcode[intcode[parameter_1_pos]] = input;
				i += 2;
				break;
			}

			// Output
			case 4:
			{
				std::cout << "Value at position " << intcode[parameter_1_pos] << ": " << std::to_string(intcode[intcode[parameter_1_pos]]) << '\n';
				i += 2;
				break;
			}

			// Jump if true
			case 5:
			{
				i = (argument_1 != 0) ? i = argument_2 : i + 3;
				break;
			}

			// Jump if false
			case 6:
			{
				i = (argument_1 == 0) ? i = argument_2 : i + 3;
				break;
			}

			// Less than
			case 7:
			{
				intcode[intcode[parameter_3_pos]] = (argument_1 < argument_2) ? 1 : 0;
				i += 4;
				break;
			}

			// Equals
			case 8:
			{
				intcode[intcode[parameter_3_pos]] = (argument_1 == argument_2) ? 1 : 0;
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