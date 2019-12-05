#include "pch.h"

std::vector<int> day_1_read_file(const std::string& path)
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

int calculate_fuel_for_mass(const int& mass)
{
	return int(std::floor(mass / 3.0) - 2);
}

void day_1()
{
	// Read file
	std::vector<int> input = day_1_read_file("C:\\Users\\Ersatz\\source\\repos\\Advent_of_Code_2019\\Advent_of_Code_2019\\src\\inputs\\day_1.txt");

	int fuel = 0;
	int total_fuel = 0;
	for (const int& i : input)
	{
		// Calculate fuel for each module
		int fuel_for_module = calculate_fuel_for_mass(i);
		fuel += fuel_for_module;
		total_fuel += fuel_for_module;

		// Calculate fuel required to launch fuel for each module
		while (calculate_fuel_for_mass(fuel_for_module) > 0)
		{
			fuel_for_module = calculate_fuel_for_mass(fuel_for_module);
			total_fuel += fuel_for_module;
		}
	}

	std::cout << "Part 1 fuel required: " << fuel << '\n'
		      << "Part 2 total fuel: " << total_fuel << '\n';
}