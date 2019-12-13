#include "pch.h"

class Moon
{
public:
	Moon(const int& x, const int& y, const int& z) :
		x(x),
		y(y),
		z(z),
		vel_x(0),
		vel_y(0),
		vel_z(0)
	{
	}

	int x;
	int y;
	int z;

	int vel_x;
	int vel_y;
	int vel_z;
};

void update_moons(std::vector<Moon>& moons)
{
	// Update velocity
	for (int current_moon = 0; current_moon < moons.size(); ++current_moon)
	{
		for (int other_moon = 0; other_moon < moons.size(); ++other_moon)
		{
			if (moons[current_moon].x != moons[other_moon].x)
			{
				moons[current_moon].vel_x += (moons[current_moon].x < moons[other_moon].x) ? 1 : -1;
			}

			if (moons[current_moon].y != moons[other_moon].y)
			{
				moons[current_moon].vel_y += (moons[current_moon].y < moons[other_moon].y) ? 1 : -1;
			}

			if (moons[current_moon].z != moons[other_moon].z)
			{
				moons[current_moon].vel_z += (moons[current_moon].z < moons[other_moon].z) ? 1 : -1;
			}
		}
	}

	// Update position
	for (Moon& moon : moons)
	{
		moon.x += moon.vel_x;
		moon.y += moon.vel_y;
		moon.z += moon.vel_z;
	}
}

int calculate_total_energy(std::vector<Moon> moons, const int& timesteps)
{
	int total_energy = 0;
	for (int i = 0; i < timesteps; ++i)
	{
		update_moons(moons);

		
	}

	// Calculate total energy
	for (const Moon& moon : moons)
	{
		total_energy += (std::abs(moon.x) + std::abs(moon.y) + std::abs(moon.z)) * (std::abs(moon.vel_x) + std::abs(moon.vel_y) + std::abs(moon.vel_z));
	}

	return total_energy;
}

long long calculate_steps_until_repitition(std::vector<Moon> moons)
{
	std::vector<int> initial_x;
	std::vector<int> initial_y;
	std::vector<int> initial_z;
	for (const Moon& moon : moons)
	{
		initial_x.push_back(moon.x);
		initial_y.push_back(moon.y);
		initial_z.push_back(moon.z);
	}

	// Get number of steps until a repitition
	long long step = 0;
	long long repeat_x = 0;
	long long repeat_y = 0;
	long long repeat_z = 0;
	while (repeat_x == 0 || repeat_y == 0 || repeat_z == 0)
	{
		++step;
		update_moons(moons);
		
		// Get current xyz values
		std::vector<int> current_x;
		std::vector<int> current_y;
		std::vector<int> current_z;
		for (const Moon& moon : moons)
		{
			current_x.push_back(moon.x);
			current_y.push_back(moon.y);
			current_z.push_back(moon.z);
		}

		// Update the step count if the step count hasn't been updated, and if the axis's are equal to their initial position
		if (repeat_x == 0 && initial_x == current_x)
		{
			repeat_x = step;
		}
		
		if (repeat_y == 0 && initial_y == current_y)
		{
			repeat_y = step;
		}

		if (repeat_z == 0 && initial_z == current_z)
		{
			repeat_z = step;
		}
	}
	return std::lcm(repeat_x + 1, std::lcm(repeat_y + 1, repeat_z + 1));
}

void day_12()
{
	Moon moon_1(8, 0, 8);
	Moon moon_2(0, -5, -10);
	Moon moon_3(16, 10, -5);
	Moon moon_4(19, -10, -7);

	std::vector<Moon> input;
	input.push_back(moon_1);
	input.push_back(moon_2);
	input.push_back(moon_3);
	input.push_back(moon_4);

	// Part 1
	int total_energy = calculate_total_energy(input, 1000);
	std::cout << "Part 1: Total energy: " << total_energy << '\n';

	// Part 2
	long long steps_until_repitition = calculate_steps_until_repitition(input);
	std::cout << "Part 2: Steps until_repitition: " << steps_until_repitition << '\n';
}