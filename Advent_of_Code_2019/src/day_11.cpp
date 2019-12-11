#include "pch.h"
#include "utility/intcode.h"
#pragma warning (disable : 26451)

class Robot
{
public:
	// Constructor
	Robot(const std::vector<long long>& program) :
		intcode(program),
		i(0),
		relative_base(0),
		done_executing(false)
	{
	}

	// Returns true if the program is done executing
	bool is_done_executing() const
	{
		return done_executing;
	}

	// Parses an intcode program and pauses if it needs to output
	long long parse(const long long& input)
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
				i += 2;
				return argument_1;
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
			// Stop
			else if (operation == 99)
			{
				done_executing = true;
				break;
			}
			else
			{
				throw std::runtime_error("Unknown opcode: " + opcode);
			}
		}
		return -99;
	}

private:
	std::vector<long long> intcode;
	int i;
	int relative_base;
	bool done_executing;
};

struct Panel
{
	int x;
	int y;
	int color;
};

bool operator==(const Panel& a, const Panel& b)
{
	return a.x == b.x && a.y == b.y;
}

bool operator!=(const Panel& a, const Panel& b)
{
	return !(a == b);
}

int day_11_part_1(const std::vector<long long>& program)
{
	Robot robot(program);
	std::vector<Panel> panels;
	int x = 0;
	int y = 0;
	int color = 0;
	int direction = 0;
	int current_rotation = 90;

	while (!robot.is_done_executing())
	{
		Panel panel;
		panel.x = x;
		panel.y = y;

		// If panel doesn't exist in vector, add it
		if (std::count(panels.begin(), panels.end(), panel) == 0)
		{
			// Get color
			color = robot.parse(0);
			panel.color = color;

			// Get direction
			direction = robot.parse(0);

			panels.push_back(panel);
		}
		// If panel already exists, update it
		else
		{
			for (Panel& p : panels)
			{
				if (p == panel)
				{
					// Get new color for panel
					long long previous_color = p.color;
					color = robot.parse(p.color);
					p.color = color;

					// Get direction
					direction = robot.parse(previous_color);
					break;
				}
			}
		}

		// Modify x and y based on direction
		if (current_rotation == 0)
		{
			if (direction == 0)
			{
				current_rotation = 90;
				++y;
			}
			else if (direction == 1)
			{
				current_rotation = 270;
				--y;
			}
		}
		else if (current_rotation == 90)
		{
			if (direction == 0)
			{
				current_rotation = 180;
				--x;
			}
			else if (direction == 1)
			{
				current_rotation = 0;
				++x;
			}
		}
		else if (current_rotation == 180)
		{
			if (direction == 0)
			{
				current_rotation = 270;
				--y;
			}
			else if (direction == 1)
			{
				current_rotation = 90;
				++y;
			}
		}
		else if (current_rotation == 270)
		{
			if (direction == 0)
			{
				current_rotation = 0;
				++x;
			}
			else if (direction == 1)
			{
				current_rotation = 180;
				--x;
			}
		}
	}
	return panels.size();
}

std::vector<Panel> day_11_part_2(const std::vector<long long>& program)
{
	Robot robot(program);
	std::vector<Panel> panels;
	int x = 0;
	int y = 0;
	int color = 0;
	int direction = 0;
	int current_rotation = 90;

	Panel start_panel;
	start_panel.x = x;
	start_panel.y = y;
	start_panel.color = 1;
	panels.push_back(start_panel);

	while (!robot.is_done_executing())
	{
		Panel panel;
		panel.x = x;
		panel.y = y;

		// If panel doesn't exist in vector, add it
		if (std::count(panels.begin(), panels.end(), panel) == 0)
		{
			// Get color
			color = robot.parse(0);
			panel.color = color;

			// Get direction
			direction = robot.parse(0);

			panels.push_back(panel);
		}
		// If panel already exists, update it
		else
		{
			for (Panel& p : panels)
			{
				if (p == panel)
				{
					// Get new color for panel
					long long previous_color = p.color;
					color = robot.parse(p.color);
					p.color = color;

					// Get direction
					direction = robot.parse(previous_color);
					break;
				}
			}
		}

		// Modify x and y based on direction
		if (current_rotation == 0)
		{
			if (direction == 0)
			{
				current_rotation = 90;
				++y;
			}
			else if (direction == 1)
			{
				current_rotation = 270;
				--y;
			}
		}
		else if (current_rotation == 90)
		{
			if (direction == 0)
			{
				current_rotation = 180;
				--x;
			}
			else if (direction == 1)
			{
				current_rotation = 0;
				++x;
			}
		}
		else if (current_rotation == 180)
		{
			if (direction == 0)
			{
				current_rotation = 270;
				--y;
			}
			else if (direction == 1)
			{
				current_rotation = 90;
				++y;
			}
		}
		else if (current_rotation == 270)
		{
			if (direction == 0)
			{
				current_rotation = 0;
				++x;
			}
			else if (direction == 1)
			{
				current_rotation = 180;
				--x;
			}
		}
	}
	return panels;
}

void day_11()
{
	std::vector<long long> program = intcode::convert_to_intcode("C:\\Users\\Ersatz\\source\\repos\\Advent_of_Code_2019\\Advent_of_Code_2019\\src\\inputs\\day_11.txt", SHRT_MAX);
	Robot robot(program);

	// Part 1
	int painted_panels = day_11_part_1(program);
	std::cout << "Part 1: Painted panels: " << painted_panels << '\n';

	// Part 2
	std::vector<Panel> panels = day_11_part_2(program);

	// Get highest x value
	int highest_x = 0;
	for (const Panel& p : panels)
	{
		if (p.x > highest_x)
		{
			highest_x = p.x;
		}
	}

	// Get lowest y value
	int lowest_y = 0;
	for (const Panel& p : panels)
	{
		if (p.y < lowest_y)
		{
			lowest_y = p.y;
		}
	}

	// Print
	// It looks messy, but it's still readable
	for (int y = 0; y >= lowest_y; --y)
	{
		for (int x = 0; x <= highest_x; ++x)
		{
			for (const Panel& p : panels)
			{
				if (p.x == x && p.y == y)
				{
					if (p.color == 1)
					{
						std::cout << '#';
					}
					else
					{
						std::cout << ' ';
					}
					break;
				}
			}
		}
		std::cout << '\n';
	}
}