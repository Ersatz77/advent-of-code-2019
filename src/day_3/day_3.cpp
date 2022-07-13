#include "day_3/day_3.h"

#include "utility/io.h"
#include "utility/string.h"
#include "utility/point.h"
#include "utility/math.h"

#include "fmt/format.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <limits>

namespace aoc
{
	struct Wire
	{
		int id;
		int steps;
	};

	static Point dir_to_delta(const char dir)
	{
		switch (dir)
		{
		case 'L':
			return { -1, 0 };
		case 'R':
			return { 1, 0 };
		case 'U':
			return { 0, 1 };
		case 'D':
			return { 0, -1 };
		default:
			return { 0, 0 };
		}
	}

	static std::unordered_map<Point, std::vector<Wire>> parse_input(const std::filesystem::path& path)
	{
		std::ifstream file = open_file(path);

		std::unordered_map<Point, std::vector<Wire>> points;
		int id = 0;
		for (std::string line; std::getline(file, line); )
		{
			Point current = Point::origin;
			int steps = 0;
			for (const auto& dir : split(line, ','))
			{
				Point delta = dir_to_delta(dir.front());
				int count = std::stoi(dir.substr(1));

				for (int i = 0; i < count; ++i)
				{
					current += delta;
					++steps;

					// Adds the current point to the map and gets a reference to the intersection vector
					auto& wires = points[current];

					// Add wire to intersection vector of it doesn't exist
					if (std::find_if(wires.begin(), wires.end(), 
						[&id](const auto& w) {return w.id == id; }) == wires.end())
					{
						wires.emplace_back(id, steps);
					}
				}
			}

			++id;
		}

		return points;
	}

	std::string Day_3::part_1(const std::filesystem::path& input_path) const
	{
		std::unordered_map<Point, std::vector<Wire>> points = parse_input(input_path / "day_3.txt");

		int closest_port = std::numeric_limits<int>::max();
		for (const auto& [point, wires] : points)
		{
			if (wires.size() > 1)
			{
				int distance = static_cast<int>(manhattan_distance(Point::origin, point));
				closest_port = std::min(closest_port, distance);
			}
		}

		return fmt::format("Closest port: {}", closest_port);
	}

	std::string Day_3::part_2(const std::filesystem::path& input_path) const
	{
		std::unordered_map<Point, std::vector<Wire>> points = parse_input(input_path / "day_3.txt");

		int fewest_steps = std::numeric_limits<int>::max();
		for (const auto& [point, wires] : points)
		{
			if (wires.size() > 1)
			{
				int total_steps = std::accumulate(wires.begin(), wires.end(), 0, [](int acc, const auto& w) { return acc + w.steps; });
				fewest_steps = std::min(fewest_steps, total_steps);
			}
		}

		return fmt::format("Fewest steps: {}", fewest_steps);
	}

} // aoc
