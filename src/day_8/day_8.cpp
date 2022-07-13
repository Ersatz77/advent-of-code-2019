#include "day_8/day_8.h"

#include "fmt/format.h"

#include <iostream>
#include <filesystem>
#include <string>

namespace aoc
{
	std::string Day_8::part_1(const std::filesystem::path& input_path) const
	{
		return fmt::format("{}", input_path.string());
	}

	std::string Day_8::part_2(const std::filesystem::path& input_path) const
	{
		return fmt::format("{}", input_path.string());
	}

} // aoc
