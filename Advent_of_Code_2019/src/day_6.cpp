#include "pch.h"

struct Orbit
{
	std::string satellite_planet_name;
	std::string planet_name;
};

bool operator==(const Orbit& o1, const Orbit& o2)
{
	return o1.planet_name == o2.planet_name && o1.satellite_planet_name == o2.satellite_planet_name;
}

std::vector<Orbit> day_6_read_file(const std::string& path)
{
	std::ifstream file;
	file.open(path);

	// Throw exception if file is not open
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file!");
	}

	// Read all lines from file and store them in a vector
	std::vector<Orbit> data;
	for (std::string line; file >> line; )
	{
		Orbit orbit;
		orbit.planet_name = line.substr(0, 3);
		orbit.satellite_planet_name = line.substr(4, 3);
		data.push_back(orbit);
	}

	// Close file and return
	file.close();
	return data;

}

Orbit get_planet_this_planet_is_a_satilite_of(const std::vector<Orbit>& input, const Orbit& orbit)
{
	for (const Orbit& o : input)
	{
		if (o.satellite_planet_name == orbit.planet_name)
		{
			return o;
		}
	}


	Orbit orbit_return;
	orbit_return.planet_name = "COM";
	orbit_return.satellite_planet_name = "COM";
	return orbit_return;
}

int get_indirect_orbits(const std::vector<Orbit>& input, const Orbit& current_orbit)
{
	int total_orbits = 0;

	if (current_orbit.planet_name != "COM")
	{
		++total_orbits;
		Orbit parent = get_planet_this_planet_is_a_satilite_of(input, current_orbit);

		while (parent.planet_name != "COM")
		{
			parent = get_planet_this_planet_is_a_satilite_of(input, parent);
			++total_orbits;
		}
	}
	return total_orbits;
}

std::vector<Orbit> get_visited_planets_to_COM(const std::vector<Orbit>& input, const Orbit& current_orbit)
{
	std::vector<Orbit> visited_planets;

	if (current_orbit.planet_name != "COM")
	{
		Orbit parent = get_planet_this_planet_is_a_satilite_of(input, current_orbit);

		while (parent.planet_name != "COM")
		{
			visited_planets.push_back(parent);
			parent = get_planet_this_planet_is_a_satilite_of(input, parent);
		}
		visited_planets.push_back(parent);
	}
	return visited_planets;
}

void day_6()
{
	// Read input
	std::vector<Orbit> orbits = day_6_read_file("C:\\Users\\Ersatz\\source\\repos\\Advent_of_Code_2019\\Advent_of_Code_2019\\src\\inputs\\day_6.txt");

	// Part 1
	// Get number of indirect orbits and direct orbits
	int total_orbits = orbits.size();
	for (const Orbit& current_orbit : orbits)
	{
		total_orbits += get_indirect_orbits(orbits, current_orbit);
	}

	std::cout << "Total orbits: " << total_orbits << '\n';

	// Part 2
	// Get minumum number of orbital transfers to reach santa

	// Get orbits of the planets YOU and SAN are at
	std::vector<Orbit> you_orbits;
	std::vector<Orbit> san_orbits;
	for (const Orbit& o : orbits)
	{
		if (o.satellite_planet_name == "YOU")
		{
			//std::cout << o.planet_name << ')' << o.satellite_planet_name << '\n';
			you_orbits = get_visited_planets_to_COM(orbits, o);
		}
		else if (o.satellite_planet_name == "SAN")
		{
			//std::cout << o.planet_name << ')' << o.satellite_planet_name << '\n';
			san_orbits = get_visited_planets_to_COM(orbits, o);
		}
	}

	// Reverse vectors so matching elements are at the front
	std::reverse(you_orbits.begin(), you_orbits.end());
	std::reverse(san_orbits.begin(), san_orbits.end());

	// Calculate how many elements from the front are identical
	int shared_orbit_pos = 0;
	while (you_orbits[shared_orbit_pos] == san_orbits[shared_orbit_pos])
	{
		++shared_orbit_pos;
	}

	// Remove identical elements
	you_orbits.erase(you_orbits.begin(), you_orbits.begin() + shared_orbit_pos);
	san_orbits.erase(san_orbits.begin(), san_orbits.begin() + shared_orbit_pos);

	int minumum_transfers = you_orbits.size() + san_orbits.size();

	std::cout << "Minumim transfers to SAN: " << minumum_transfers << '\n';
}