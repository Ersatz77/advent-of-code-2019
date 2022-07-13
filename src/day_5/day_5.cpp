#include "day_5/day_5.h"

#include "intcode/vm.h"
#include "intcode/program_io.h"

#include "fmt/format.h"

#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <cstdint>

namespace aoc
{
	std::string Day_5::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<int64_t> program = intcode::read_file(input_path / "day_5.txt");

		intcode::Vm vm(program);
		vm.push_input(1);
		while (!vm.is_halted())
		{
			vm.run();
		}

		std::string output;
		for (size_t i = vm.output_size(); i > 1; --i)
		{
			output += fmt::format("Check code: {}\n", vm.pop_output());
		}

		output += fmt::format("Diagnostic code: {}", vm.pop_output());
		return output;
	}

	std::string Day_5::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<int64_t> program = intcode::read_file(input_path / "day_5.txt");

		intcode::Vm vm(program);
		vm.push_input(5);
		while (!vm.is_halted())
		{
			vm.run();
		}

		std::string output;
		for (size_t i = vm.output_size(); i > 1; --i)
		{
			output += fmt::format("Check code: {}\n", vm.pop_output());
		}

		output += fmt::format("Diagnostic code: {}", vm.pop_output());

		return output;
	}

} // aoc
