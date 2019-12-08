#include "pch.h"

// Read file and return contents in an int vector
std::vector<int> day_8_read_file(const std::string& path)
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

void day_8()
{
	constexpr int width = 25;
	constexpr int height = 6;
	constexpr int resolution = width * height;
	std::vector<int> pixels = day_8_read_file("C:\\Users\\Ersatz\\source\\repos\\Advent_of_Code_2019\\Advent_of_Code_2019\\src\\inputs\\day_8.txt");
	std::vector<std::vector<int>> layers(pixels.size() / (resolution));
	
	// Add pixels to each layer
	int pointer = 0;
	int max_pixels = resolution;
	for (std::vector<int>& layer : layers)
	{
		while (pointer < max_pixels)
		{
			layer.push_back(pixels[pointer]);
			++pointer;
		}

		max_pixels += resolution;
	}

	// Part 1
	// Get layer with fewest zeros
	int zeros = INT_MAX;
	std::vector<int> selected_layer;
	for (const std::vector<int>& layer : layers)
	{
		int zero_count = std::count(layer.begin(), layer.end(), 0);
		if (zero_count < zeros)
		{
			zeros = zero_count;
			selected_layer = layer;
		}
	}

	// Get number of 1's and 2's from that layer and multiply them
	int output = std::count(selected_layer.begin(), selected_layer.end(), 1) * std::count(selected_layer.begin(), selected_layer.end(), 2);
	std::cout << "Part 1: " << output << '\n';

	// Part 2
	std::cout << "Part 2:\n";

	// Calculate output layer
	std::vector<int> output_layer;
	for (int i = 0; i < resolution; ++i)
	{
		for (const std::vector<int>& layer : layers)
		{
			int current_pixel = layer[i];
			if (current_pixel != 2)
			{
				output_layer.push_back(current_pixel);
				break;
			}
		}
	}

	// Print layer
	for (int i = 0; i < resolution; ++i)
	{
		// White
		if (output_layer[i] == 1)
		{
			std::cout << '#';
		}
		// Black
		else
		{
			std::cout << ' ';
		}

		// Print newline
		if (i % width == width - 1)
		{
			std::cout << '\n';
		}
	}
}