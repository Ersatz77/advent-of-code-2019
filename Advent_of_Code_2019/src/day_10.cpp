#include "pch.h"

constexpr int width = 27;
constexpr int height = 27;

struct Asteroid
{
	int x;
	int y;
	double distance;
};

bool operator==(const Asteroid& a1, const Asteroid& a2)
{
	return  a1.x == a2.x && a1.y == a2.y;
}

bool operator!=(const Asteroid& a1, const Asteroid& a2)
{
	return  !(a1 == a2);
}

bool operator<(const Asteroid& a1, const Asteroid& a2)
{
	return a1.distance < a2.distance;
}

// Read file and return contents in an asteroid vector
std::vector<Asteroid> day_10_read_file(const std::string& path)
{
	std::ifstream file;
	file.open(path);

	// Throw exception if file is not open
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file!");
	}

	// Read all lines from file and store them in a vector
	std::vector<Asteroid> data;
	for (int y = 1; y <= height; ++y)
	{
		for (int x = 1; x <= width; ++x)
		{
			char c = ' ';
			file >> c;

			if (c == '#')
			{
				Asteroid asteroid;
				asteroid.x = x;
				asteroid.y = y;
				data.push_back(asteroid);
			}
		}
	}

	// Close file and return
	file.close();
	return data;
}

// Returns the angle between two asteroids in degrees
double angle(const Asteroid& a, const Asteroid& b)
{
	return atan2(a.y - b.y, a.x - b.x) * (180 / M_PI);
}

// Get the distance between two asteroids
double distance(const Asteroid& a, const Asteroid& b)
{
	return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

void day_10()
{
	std::vector<Asteroid> asteroids = day_10_read_file("C:\\Users\\Ersatz\\source\\repos\\Advent_of_Code_2019\\Advent_of_Code_2019\\src\\inputs\\day_10.txt");


	// Part 1
	int observable_asteroids = 0;

	Asteroid best_asteroid;
	best_asteroid.x = 0;
	best_asteroid.y = 0;

	for (const Asteroid& current_asteroid : asteroids)
	{
		//std::cout << "Angles from asteroid at: " << current_asteroid.x << ' ' << current_asteroid.y << '\n';
		std::vector<double> angles;
		for (const Asteroid& checked_asteroid : asteroids)
		{
			if (current_asteroid != checked_asteroid)
			{
				double angle_between = angle(current_asteroid, checked_asteroid);

				// Correct negative angles
				if (angle_between < 0)
				{
					angle_between += 360;
				}

				// Only add angle to vector if that angle has not already been added
				if (std::count(angles.begin(), angles.end(), angle_between) == 0)
				{
					angles.push_back(angle_between);
				}
			}
		}

		// Override greatest value if the current asteriod can see more
		if (angles.size() > observable_asteroids)
		{
			best_asteroid = current_asteroid;
			observable_asteroids = angles.size();
		}
	}

	// Part 2
	std::map<double, std::vector<Asteroid>> angle_map;
	for (const Asteroid& a : asteroids)
	{
		if (a != best_asteroid)
		{
			//std::cout << '(' << a.x << ',' << a.y << ") " << a.distance << '\n';
			double angle_between = angle(a, best_asteroid);
			double distance_between = distance(a, best_asteroid);

			// Correct negative angles
			if (angle_between < 0)
			{
				angle_between += 360;
			}

			Asteroid asteroid_to_sort = a;
			asteroid_to_sort.distance = distance_between;
			angle_map[angle_between].push_back(asteroid_to_sort);
		}
	}

	// Sort each asteroid vector in map based on their distance
	for (auto& a : angle_map)
	{
		std::sort(a.second.begin(), a.second.end());
		//std::reverse(a.second.begin(), a.second.end());
	}
	
	// Destroy asteroids
	std::vector<Asteroid> destroyed_asteroids;
	for (auto& a : angle_map)
	{
		// Only remove elements from vector if it's not empty
		if (a.second.size() > 0)
		{
			destroyed_asteroids.push_back(a.second.back());
			a.second.pop_back();
		}
	}
		
	for (const Asteroid a : destroyed_asteroids)
	{
		std::cout << '(' << a.x << ',' << a.y << ") " << a.distance << '\n';
	}

	Asteroid last_asteroid = destroyed_asteroids[199];
	
	// Output
	std::cout << "Part 1: Best asteroid is at (" << best_asteroid.x - 1 << ',' << best_asteroid.y - 1 << ") and can view " << observable_asteroids << " asteroids\n";
	std::cout << "Part 2: 200th asteroid to be destroyed: (" << last_asteroid.x - 1 << ',' << last_asteroid.y - 1 << ") Output: " <<  ((last_asteroid.x - 1) * 100) + (last_asteroid.y - 1) << '\n';
}