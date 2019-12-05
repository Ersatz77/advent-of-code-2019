#include "pch.h"

struct Point
{
	int x;
	int y;
	int steps;
};

bool operator==(const Point& point_1, const Point& point_2)
{
	return point_1.x == point_2.x && point_1.y == point_2.y;
}

std::vector<Point> day_3_read_file(const std::string& path)
{
	// Open file
	std::ifstream file;
	file.open(path);

	// Throw exception if file is not open
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file!");
	}

	// Read all lines and store them as points the wire travels through
	std::vector<Point> data;

	char direction = ' ';
	int steps = 0;
	int combined_steps = 0;

	int x = 0;
	int y = 0;

	while (file >> direction >> steps)
	{
		for (int i = 0; i < steps; ++i)
		{
			switch (direction)
			{
				case 'U':
					++y;
					break;

				case 'D':
					--y;
					break;

				case 'R':
					++x;
					break;

				case 'L':
					--x;
					break;
			}

			++combined_steps;

			Point point;
			point.x = x;
			point.y = y;
			point.steps = combined_steps;


			data.push_back(point);
		}
	}

	// Close file and return
	file.close();
	return data;
}

void day_3()
{
	// Get input
	std::vector<Point> wire_1 = day_3_read_file("C:\\Users\\Ersatz\\source\\repos\\Advent_of_Code_2019\\Advent_of_Code_2019\\src\\inputs\\day_3_1.txt");
	std::vector<Point> wire_2 = day_3_read_file("C:\\Users\\Ersatz\\source\\repos\\Advent_of_Code_2019\\Advent_of_Code_2019\\src\\inputs\\day_3_2.txt");

	// Get manhatten distance from every point that intersects and override distance if it's smaller
	// |x1 - x2| + |y1 - y2|
	int distance = INT_MAX;
	int steps = INT_MAX;
	for (const Point& point_1 : wire_1)
	{
		for (const Point& point_2 : wire_2)
		{
			if (point_1 == point_2)
			{
				int manhatten_distance = std::abs(point_1.x) + std::abs(point_1.y);
				int combined_steps = point_1.steps + point_2.steps;

				// Override lowest manhatten distance
				if (manhatten_distance < distance)
				{
					distance = manhatten_distance;
				}

				// Override lowest number of combined steps
				if (combined_steps < steps)
				{
					steps = combined_steps;
				}

				std::cout << "Intersection at: (" << point_1.x << ',' << point_1.y << ") Distance: " << manhatten_distance << " Combined steps: " << combined_steps << '\n';
			}
		}
	}

	std::cout << "Closest intersection distance: " << distance << '\n';
	std::cout << "Lowest number of combined steps: " << steps << '\n';
}