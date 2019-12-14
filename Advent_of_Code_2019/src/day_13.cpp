#include "pch.h"
#include "utility/intcode.h"
#pragma warning (disable : 26451)

enum class Tile_id
{
	EMPTY = 0,
	WALL,
	BLOCK,
	HORIZONTAL_PADDLE,
	BALL
};

struct Tile
{
	int x;
	int y;
	Tile_id id;
};

std::vector<long long> arcade_parse(std::vector<long long> intcode)
{
	// Parse intcode
	std::vector<long long> output;
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
			//std::cout << "Input: ";
			//std::cin >> input;
			//std::cout << '\n';

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

			output.push_back(argument_1);

			if (output.back() > 17000)
			{
				std::cout << "Part 2: Score: " << output.back() << '\n';
			}

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
	return output;
}

void print_display(const std::vector<Tile> tiles)
{
	for (int y = 0; y <= 22; ++y)
	{
		for (int x = 0; x <= 42; ++x)
		{
			for (const Tile& tile : tiles)
			{
				if (tile.x == x && tile.y == y)
				{
					switch (tile.id)
					{
						case Tile_id::EMPTY:
							std::cout << ' ';
							break;
						case Tile_id::WALL:
							std::cout << '#';
							break;
						case Tile_id::BLOCK:
							std::cout << '=';
							break;
						case Tile_id::HORIZONTAL_PADDLE:
							std::cout << '_';
							break;
						case Tile_id::BALL:
							std::cout << '*';
							break;
					}
				}
			}
		}
		std::cout << '\n';
	}
}

void day_13()
{
	std::vector<long long> program_1 = intcode::convert_to_intcode("C:\\Users\\Ersatz\\source\\repos\\Advent_of_Code_2019\\Advent_of_Code_2019\\src\\inputs\\day_13.txt", SHRT_MAX);
	std::vector<long long> program_2 = program_1;
	program_2[0] = 2;


	// Part 1
	std::vector<long long> output_1 = arcade_parse(program_1);

	// Create tiles and count number of block tiles
	std::vector<Tile> tiles;
	int block_tiles = 0;
	for (int i = 0; i < output_1.size(); i += 3)
	{
		Tile tile;
		tile.x = output_1[i];
		tile.y = output_1[i + 1];
		tile.id = Tile_id(output_1[i + 2]);

		if (tile.id == Tile_id::BLOCK)
		{
			++block_tiles;
		}

		tiles.push_back(tile);
	}

	// Print display
	print_display(tiles);
	std::cout << "Part 1: Number of block tiles: " << block_tiles << '\n';

	// Part 2
	// Bottom empty tiles have been turned into wall tiles so you can never lose
	std::vector<long long> output_2 = arcade_parse(program_2);
}