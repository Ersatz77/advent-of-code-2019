#include "day_2/day_2.h"

#include "intcode/basic_vm.h"
#include "intcode/program_io.h"

#include "fmt/format.h"

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <cstdint>

namespace aoc
{
	static int64_t find_pair(const std::vector<int64_t>& program)
	{
		constexpr int64_t target_output = 19690720;
		for (int64_t noun = 0; noun <= 99; ++noun)
		{
			for (int64_t verb = 0; verb <= 99; ++verb)
			{
				intcode::Basic_vm vm(program);

				vm[1] = noun;
				vm[2] = verb;
				vm.run();

				if (vm[0] == target_output)
				{
					return noun * 100 + verb;
				}
			}
		}

		return 0;
	}

	std::string Day_2::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<int64_t> program = intcode::read_file(input_path / "day_2.txt");
		intcode::Basic_vm vm(program);

		vm[1] = 12;
		vm[2] = 2;
		vm.run();

		return fmt::format("Value left at pos 0: {}", vm[0]);
	}

	std::string Day_2::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<int64_t> program = intcode::read_file(input_path / "day_2.txt");
		int64_t pair = find_pair(program);
		return fmt::format("Noun/verb pair: {}", pair);
	}

} // aoc
