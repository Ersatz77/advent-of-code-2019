#pragma once
#include <vector>
#include <string>

namespace intcode
{
	// Convert file to intcode
	std::vector<long long> convert_to_intcode(const std::string& path, const int& extra_memory_locations);

	// Parse intcode
	void parse(std::vector<long long> intcode);
}