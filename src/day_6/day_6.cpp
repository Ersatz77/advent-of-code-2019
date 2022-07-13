#include "day_6/day_6.h"

#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <unordered_map>
#include <iterator>

namespace aoc
{
	static std::unordered_map<std::string, std::string> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::unordered_map<std::string, std::string> orbits;
		for (std::string line; std::getline(file, line); )
		{
			orbits[line.substr(4, 3)] = line.substr(0, 3);
		}

		return orbits;
	}

	static std::vector<std::string> transfers_to_com(const std::string& planet, const std::unordered_map<std::string, std::string>& orbits)
	{
		std::vector<std::string> path;
		for (std::string current = orbits.at(planet); current != "COM"; current = orbits.at(current))
		{
			path.push_back(current);
		}

		return path;
	}

	std::string Day_6::part_1(const std::filesystem::path& input_path) const
	{
		std::unordered_map<std::string, std::string> orbits = parse_input(input_path / "day_6.txt");

		// Find total direct and indirect orbits
		uint64_t total_orbits = 0;
		for (const auto& orbit : orbits)
		{
			for (std::string current = orbit.first; current != "COM"; current = orbits.at(current))
			{
				++total_orbits;
			}
		}

		return fmt::format("Total direct and indirect orbits: {}", total_orbits);
	}

	std::string Day_6::part_2(const std::filesystem::path& input_path) const
	{
		std::unordered_map<std::string, std::string> orbits = parse_input(input_path / "day_6.txt");

		std::vector<std::string> you_path = transfers_to_com("YOU", orbits);
		std::vector<std::string> san_path = transfers_to_com("SAN", orbits);

		// Increment both iterators until the values they point to aren't the same
		auto you_path_it = you_path.rbegin();
		auto san_path_it = san_path.rbegin();
		while (*you_path_it == *san_path_it && you_path_it != you_path.rend() && san_path_it != san_path.rend())
		{
			++you_path_it;
			++san_path_it;
		}

		// While the last shared orbit is not being pointed at by the iterators, 
		// summing the distance of the current iterator pos to their end is enough to 
		// get the correct number of transfers.
		uint64_t transfers = std::distance(you_path_it, you_path.rend()) + std::distance(san_path_it, san_path.rend());

		return fmt::format("Minimum transfers from YOU to SAN: {}", transfers);
	}

} // aoc
