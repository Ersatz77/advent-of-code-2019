#include "pch.h"

class Amplifier
{
public:
	// Constructor
	Amplifier(const std::vector<int> program, const int& phase):
		intcode(program),
		phase_setting(phase),
		i(0),
		previous_output(0),
		has_read_phase(false),
		done_executing(false)
	{
	}

	// Getters
	bool is_done_executing() const { return done_executing; }

	// Parse intcode
	int parse(const int& input)
	{
		while (i < intcode.size())
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
				int argument_1 = (parameter_1_mode == 1) ? intcode[i + 1] : intcode[intcode[i + 1]];
				int argument_2 = (parameter_2_mode == 1) ? intcode[i + 2] : intcode[intcode[i + 2]];
				intcode[intcode[i + 3]] = argument_1 + argument_2;
				i += 4;
			}
			// Multiply
			else if (operation == 2)
			{
				int argument_1 = (parameter_1_mode == 1) ? intcode[i + 1] : intcode[intcode[i + 1]];
				int argument_2 = (parameter_2_mode == 1) ? intcode[i + 2] : intcode[intcode[i + 2]];
				intcode[intcode[i + 3]] = argument_1 * argument_2;
				i += 4;
			}
			// Input
			else if (operation == 3)
			{
				if (!has_read_phase)
				{
					intcode[intcode[i + 1]] = phase_setting;
					has_read_phase = true;
				}
				else
				{
					intcode[intcode[i + 1]] = input;
				}
				i += 2;
			}
			// Output
			else if (operation == 4)
			{
				int output = intcode[intcode[i + 1]];
				previous_output = output;
				i += 2;
				return output;
			}
			// Jump if true
			else if (operation == 5)
			{
				int argument_1 = (parameter_1_mode == 1) ? intcode[i + 1] : intcode[intcode[i + 1]];
				int argument_2 = (parameter_2_mode == 1) ? intcode[i + 2] : intcode[intcode[i + 2]];
				i = (argument_1 != 0) ? i = argument_2 : i + 3;
			}
			// Jump if false
			else if (operation == 6)
			{
				int argument_1 = (parameter_1_mode == 1) ? intcode[i + 1] : intcode[intcode[i + 1]];
				int argument_2 = (parameter_2_mode == 1) ? intcode[i + 2] : intcode[intcode[i + 2]];
				i = (argument_1 == 0) ? i = argument_2 : i + 3;
			}
			// Less than
			else if (operation == 7)
			{
				int argument_1 = (parameter_1_mode == 1) ? intcode[i + 1] : intcode[intcode[i + 1]];
				int argument_2 = (parameter_2_mode == 1) ? intcode[i + 2] : intcode[intcode[i + 2]];
				intcode[intcode[i + 3]] = (argument_1 < argument_2) ? 1 : 0;
				i += 4;
			}
			// Equals
			else if (operation == 8)
			{
				int argument_1 = (parameter_1_mode == 1) ? intcode[i + 1] : intcode[intcode[i + 1]];
				int argument_2 = (parameter_2_mode == 1) ? intcode[i + 2] : intcode[intcode[i + 2]];
				intcode[intcode[i + 3]] = (argument_1 == argument_2) ? 1 : 0;
			}
			// Stop
			else if (operation == 99)
			{
				done_executing = true;
				return previous_output;
			}
			// Unknown operation
			else
			{
				throw std::runtime_error("Unknown operation");
			}
		}
	}

private:
	std::vector<int> intcode;
	int phase_setting;
	int i;
	int previous_output;
	bool has_read_phase;
	bool done_executing;
};

// Read file and return contents in an int vector
std::vector<int> day_7_read_file(const std::string& path)
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

int amp_circuit(const std::vector<int>& program, const int& phase_setting_1, const int& phase_setting_2, const int& phase_setting_3, const int& phase_setting_4, const int& phase_setting_5, const int& input)
{
	Amplifier amp_1(program, phase_setting_1);
	Amplifier amp_2(program, phase_setting_2);
	Amplifier amp_3(program, phase_setting_3);
	Amplifier amp_4(program, phase_setting_4);
	Amplifier amp_5(program, phase_setting_5);

	int amp_1_output = amp_1.parse(input);
	int amp_2_output = amp_2.parse(amp_1_output);
	int amp_3_output = amp_3.parse(amp_2_output);
	int amp_4_output = amp_4.parse(amp_3_output);
	return amp_5.parse(amp_4_output);
}

int amp_circuit_looping(const std::vector<int>& program, const int& phase_setting_1, const int& phase_setting_2, const int& phase_setting_3, const int& phase_setting_4, const int& phase_setting_5, const int& input)
{
	Amplifier amp_1(program, phase_setting_1);
	Amplifier amp_2(program, phase_setting_2);
	Amplifier amp_3(program, phase_setting_3);
	Amplifier amp_4(program, phase_setting_4);
	Amplifier amp_5(program, phase_setting_5);

	int total = input;
	while (!amp_5.is_done_executing())
	{
		int amp_1_output = amp_1.parse(total);
		int amp_2_output = amp_2.parse(amp_1_output);
		int amp_3_output = amp_3.parse(amp_2_output);
		int amp_4_output = amp_4.parse(amp_3_output);
		total = amp_5.parse(amp_4_output);
	}

	return total;
}

int calculate_maximum_thrust(const std::vector<int> program, const int& phase_min, const int& phase_max, const int& input, const bool& is_looping)
{
	// Get all possible digits between range
	std::vector<int> unique_digits;
	for (int x = phase_min; x <= phase_max; ++x)
	{
		unique_digits.push_back(x);
	}

	// Calculate maximum thrust
	int maximum_thrust = INT_MIN;
	for (int i = phase_min; i <= phase_max; ++i)
	{
		for (int j = phase_min; j <= phase_max; ++j)
		{
			for (int k = phase_min; k <= phase_max; ++k)
			{
				for (int l = phase_min; l <= phase_max; ++l)
				{
					for (int m = phase_min; m <= phase_max; ++m)
					{
						// Check phase settings to make sure each setting only appears once;
						std::vector<int> phase_settings = { i, j, k, l, m };
						int num_0 = std::count(phase_settings.begin(), phase_settings.end(), unique_digits[0]);
						int num_1 = std::count(phase_settings.begin(), phase_settings.end(), unique_digits[1]);
						int num_2 = std::count(phase_settings.begin(), phase_settings.end(), unique_digits[2]);
						int num_3 = std::count(phase_settings.begin(), phase_settings.end(), unique_digits[3]);
						int num_4 = std::count(phase_settings.begin(), phase_settings.end(), unique_digits[4]);

						if (num_0 == 1 && num_1 == 1 && num_2 == 1 && num_3 == 1 && num_4 == 1)
						{
							int amp_output = is_looping ? amp_circuit_looping(program, i, j, k, l, m, input) : amp_circuit(program, i, j, k, l, m, input);
							if (amp_output > maximum_thrust)
							{
								maximum_thrust = amp_output;
							}
						}
					}
				}
			}
		}
	}
	return maximum_thrust;
}

void day_7()
{
	// Get amplifier program from input
	std::vector<int> program = day_7_read_file("C:\\Users\\Ersatz\\source\\repos\\Advent_of_Code_2019\\Advent_of_Code_2019\\src\\inputs\\day_7.txt");

	// Print results
	std::cout << "Part 1 maximum thrust: " << calculate_maximum_thrust(program, 0, 4, 0, false) << '\n';
	std::cout << "Part 2 maximum thrust: " << calculate_maximum_thrust(program, 5, 9, 0, true) << '\n';
}