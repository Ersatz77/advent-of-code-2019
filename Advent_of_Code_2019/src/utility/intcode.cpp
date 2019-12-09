#include "intcode.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#pragma warning (disable : 26451)

namespace intcode
{
	// Convert file to intcode
	std::vector<long long> convert_to_intcode(const std::string& path, const int& extra_memory_locations)
	{
		std::ifstream file;
		file.open(path);

		// Throw exception if file is not open
		if (!file.is_open())
		{
			throw std::runtime_error("Could not open file!");
		}

		// Read all lines from file and store them in a vector
		std::vector<long long> data;
		for (long long line = 0; file >> line; )
		{
			data.push_back(line);
		}

		// Add extra memory locations after input data
		for (int i = 0; i < extra_memory_locations; ++i)
		{
			data.push_back(0);
		}

		// Close file and return
		file.close();
		return data;
	}

	// Parse intcode
	void parse(std::vector<long long> intcode)
	{
		// Parse intcode
		int relative_base = 0;
		for (int i = 0; intcode[i] != 99; )
		{
			// Get opcode, operation, and the mode for each parameter
			std::string opcode = std::to_string(intcode[i]);
			opcode.insert(0, 5 - opcode.length(), '0');

			int operation = std::stoi(opcode.substr(3, 2));

			int parameter_1_mode = opcode[2] - int('0');
			int parameter_2_mode = opcode[1] - int('0');
			int parameter_3_mode = opcode[0] - int('0');

			// Add
			if (operation == 1)
			{
				long long argument_1 = 0;
				switch (parameter_1_mode)
				{
					case 0:
						argument_1 = intcode[intcode[i + 1]];
						break;
					case 1:
						argument_1 = intcode[i + 1];
						break;
					case 2:
						argument_1 = intcode[intcode[i + 1] + relative_base];
						break;
				}

				long long argument_2 = 0;
				switch (parameter_2_mode)
				{
					case 0:
						argument_2 = intcode[intcode[i + 2]];
						break;
					case 1:
						argument_2 = intcode[i + 2];
						break;
					case 2:
						argument_2 = intcode[intcode[i + 2] + relative_base];
						break;
				}

				long long output = argument_1 + argument_2;
				switch (parameter_3_mode)
				{
					case 0:
						intcode[intcode[i + 3]] = output;
						break;
					case 1:
						intcode[i + 3] = output;
						break;
					case 2:
						intcode[intcode[i + 3] + relative_base] = output;
						break;
				}

				i += 4;
			}
			// Multiply
			else if (operation == 2)
			{
				long long argument_1 = 0;
				switch (parameter_1_mode)
				{
					case 0:
						argument_1 = intcode[intcode[i + 1]];
						break;
					case 1:
						argument_1 = intcode[i + 1];
						break;
					case 2:
						argument_1 = intcode[intcode[i + 1] + relative_base];
						break;
				}

				long long argument_2 = 0;
				switch (parameter_2_mode)
				{
					case 0:
						argument_2 = intcode[intcode[i + 2]];
						break;
					case 1:
						argument_2 = intcode[i + 2];
						break;
					case 2:
						argument_2 = intcode[intcode[i + 2] + relative_base];
						break;
				}

				long long output = argument_1 * argument_2;
				switch (parameter_3_mode)
				{
					case 0:
						intcode[intcode[i + 3]] = output;
						break;
					case 1:
						intcode[i + 3] = output;
						break;
					case 2:
						intcode[intcode[i + 3] + relative_base] = output;
						break;
				}

				i += 4;
			}
			// Input
			else if (operation == 3)
			{
				long long input = 0;
				std::cout << "Input: ";
				std::cin >> input;
				std::cout << '\n';

				switch (parameter_1_mode)
				{
					case 0:
						intcode[intcode[i + 1]] = input;
						break;
					case 1:
						intcode[i + 1] = input;
						break;
					case 2:
						intcode[intcode[i + 1] + relative_base] = input;
						break;
				}

				i += 2;
			}
			// Output
			else if (operation == 4)
			{
				long long argument_1 = 0;
				switch (parameter_1_mode)
				{
					case 0:
						argument_1 = intcode[intcode[i + 1]];
						break;
					case 1:
						argument_1 = intcode[i + 1];
						break;
					case 2:
						argument_1 = intcode[intcode[i + 1] + relative_base];
						break;
				}

				std::cout << "Output: " << std::to_string(argument_1) << '\n';
				i += 2;
			}
			// Jump if true
			else if (operation == 5)
			{
				long long argument_1 = 0;
				switch (parameter_1_mode)
				{
					case 0:
						argument_1 = intcode[intcode[i + 1]];
						break;
					case 1:
						argument_1 = intcode[i + 1];
						break;
					case 2:
						argument_1 = intcode[intcode[i + 1] + relative_base];
						break;
				}

				long long argument_2 = 0;
				switch (parameter_2_mode)
				{
					case 0:
						argument_2 = intcode[intcode[i + 2]];
						break;
					case 1:
						argument_2 = intcode[i + 2];
						break;
					case 2:
						argument_2 = intcode[intcode[i + 2] + relative_base];
						break;
				}

				i = (argument_1 != 0) ? i = argument_2 : i + 3;
			}
			// Jump if false
			else if (operation == 6)
			{
				long long argument_1 = 0;
				switch (parameter_1_mode)
				{
					case 0:
						argument_1 = intcode[intcode[i + 1]];
						break;
					case 1:
						argument_1 = intcode[i + 1];
						break;
					case 2:
						argument_1 = intcode[intcode[i + 1] + relative_base];
						break;
				}

				long long argument_2 = 0;
				switch (parameter_2_mode)
				{
					case 0:
						argument_2 = intcode[intcode[i + 2]];
						break;
					case 1:
						argument_2 = intcode[i + 2];
						break;
					case 2:
						argument_2 = intcode[intcode[i + 2] + relative_base];
						break;
				}
				i = (argument_1 == 0) ? i = argument_2 : i + 3;
			}
			// Less than
			else if (operation == 7)
			{
				long long argument_1 = 0;
				switch (parameter_1_mode)
				{
					case 0:
						argument_1 = intcode[intcode[i + 1]];
						break;
					case 1:
						argument_1 = intcode[i + 1];
						break;
					case 2:
						argument_1 = intcode[intcode[i + 1] + relative_base];
						break;
				}

				long long argument_2 = 0;
				switch (parameter_2_mode)
				{
					case 0:
						argument_2 = intcode[intcode[i + 2]];
						break;
					case 1:
						argument_2 = intcode[i + 2];
						break;
					case 2:
						argument_2 = intcode[intcode[i + 2] + relative_base];
						break;
				}

				long long output = (argument_1 < argument_2) ? 1 : 0;
				switch (parameter_3_mode)
				{
					case 0:
						intcode[intcode[i + 3]] = output;
						break;
					case 1:
						intcode[i + 3] = output;
						break;
					case 2:
						intcode[intcode[i + 3] + relative_base] = output;
						break;
				}

				i += 4;
			}
			// Equals
			else if (operation == 8)
			{
				long long argument_1 = 0;
				switch (parameter_1_mode)
				{
					case 0:
						argument_1 = intcode[intcode[i + 1]];
						break;
					case 1:
						argument_1 = intcode[i + 1];
						break;
					case 2:
						argument_1 = intcode[intcode[i + 1] + relative_base];
						break;
				}

				long long argument_2 = 0;
				switch (parameter_2_mode)
				{
					case 0:
						argument_2 = intcode[intcode[i + 2]];
						break;
					case 1:
						argument_2 = intcode[i + 2];
						break;
					case 2:
						argument_2 = intcode[intcode[i + 2] + relative_base];
						break;
				}

				long long output = (argument_1 == argument_2) ? 1 : 0;
				switch (parameter_3_mode)
				{
					case 0:
						intcode[intcode[i + 3]] = output;
						break;
					case 1:
						intcode[i + 3] = output;
						break;
					case 2:
						intcode[intcode[i + 3] + relative_base] = output;
						break;
				}

				i += 4;
			}
			// Change relative base
			else if (operation == 9)
			{
				long long argument_1 = 0;
				switch (parameter_1_mode)
				{
					case 0:
						relative_base += intcode[intcode[i + 1]];
						break;
					case 1:
						relative_base += intcode[i + 1];
						break;
					case 2:
						relative_base += intcode[intcode[i + 1] + relative_base];
						break;
				}

				i += 2;
			}
			else
			{
				throw std::runtime_error("Unknown operation!");
			}
		}
	}
}