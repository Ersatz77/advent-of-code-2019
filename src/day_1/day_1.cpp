#include "day_1/day_1.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

namespace aoc
{
	static std::vector<int> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);
		std::vector<int> module_masses;
		for (int mass = 0; file >> mass; )
		{
			module_masses.push_back(mass);
		}

		return module_masses;
	}

	std::string Day_1::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<int> module_masses = parse_input(input_path / "day_1.txt");

		int total_fuel = 0;
		for (const int mass : module_masses)
		{
			total_fuel += (mass / 3) - 2;
		}

		return fmt::format("Total fuel: {}", total_fuel);
	}

	std::string Day_1::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<int> module_masses = parse_input(input_path / "day_1.txt");

		int total_fuel = 0;
		for (int mass : module_masses)
		{
			while ((mass / 3) - 2 > 0)
			{
				mass = (mass / 3) - 2;
				total_fuel += mass;
			}
		}

		return fmt::format("Total fuel: {}", total_fuel);
	}

} // aoc
