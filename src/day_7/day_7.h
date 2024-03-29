#ifndef AOC_2019_DAY_7_H
#define AOC_2019_DAY_7_H

#include "utility/day.h"

#include <filesystem>
#include <string>

namespace aoc
{
	class Day_7 : public Day
	{
		virtual std::string part_1(const std::filesystem::path& input_path) const override;
		virtual std::string part_2(const std::filesystem::path& input_path) const override;
	};

} // aoc

#endif // !AOC_2019_DAY_7_H
