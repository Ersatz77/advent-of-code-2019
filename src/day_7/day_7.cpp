#include "day_7/day_7.h"

#include "intcode/vm.h"
#include "intcode/program_io.h"

#include "fmt/format.h"

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <cstdint>

namespace aoc
{
	static std::array<intcode::Vm, 5> create_amps(const std::vector<int64_t>& program, const std::array<int64_t, 5>& phase_settings)
	{
		std::array<intcode::Vm, 5> amps = {
			intcode::Vm(program),
			intcode::Vm(program),
			intcode::Vm(program),
			intcode::Vm(program),
			intcode::Vm(program)
		};

		for (size_t i = 0; i < amps.size(); ++i)
		{
			amps[i].push_input(phase_settings[i]);
		}

		return amps;
	}

	static bool is_valid_phase_settings(const std::array<int64_t, 5>& phase_settings)
	{
		std::unordered_map<uint64_t, size_t> counts;
		for (const auto& i : phase_settings)
		{
			++counts[i];
		}

		return std::all_of(counts.begin(), counts.end(), [](const auto& kv) { return kv.second == 1; });
	}

	static int64_t run_amp_series(std::array<intcode::Vm, 5>& amps, const int64_t start)
	{
		int64_t accumulation = start;
		for (auto& vm : amps)
		{
			vm.push_input(accumulation);
			while (!vm.is_halted() && !vm.has_output())
			{
				vm.run();
			}

			if (vm.has_output())
			{
				accumulation = vm.pop_output();
			}
		}

		return accumulation;
	}

	static int64_t find_largest_output(const std::vector<int64_t>& program, const int64_t min, const int64_t max, 
		std::function<int64_t(std::array<intcode::Vm, 5>&)> circuit_func)
	{
		int64_t largest_output = 0;
		for (int64_t a = min; a <= max; ++a)
		{
			for (int64_t b = min; b <= max; ++b)
			{
				for (int64_t c = min; c <= max; ++c)
				{
					for (int64_t d = min; d <= max; ++d)
					{
						for (int64_t e = min; e <= max; ++e)
						{
							// Skip invalid phase settings
							if (!is_valid_phase_settings({ a, b, c, d, e }))
								continue;

							std::array<intcode::Vm, 5> amps = create_amps(program, { a, b, c, d, e });
							largest_output = std::max(circuit_func(amps), largest_output);
						}
					}
				}
			}
		}

		return largest_output;
	}

	std::string Day_7::part_1(const std::filesystem::path& input_path) const
	{
		std::vector<int64_t> program = intcode::read_file(input_path / "day_7.txt");

		int64_t largest_output = find_largest_output(program, 0, 4,
			[](auto& amps) {
				return run_amp_series(amps, 0);
			});

		return fmt::format("Largest amp output: {}", largest_output);
	}

	std::string Day_7::part_2(const std::filesystem::path& input_path) const
	{
		std::vector<int64_t> program = intcode::read_file(input_path / "day_7.txt");

		int64_t largest_output = find_largest_output(program, 5, 9,
			[](auto& amps) {
				int64_t accumulation = 0;
				while (!amps.back().is_halted())
				{
					accumulation = run_amp_series(amps, accumulation);
				}

				return accumulation;
			});

		return fmt::format("Largest amp output: {}", largest_output);
	}

} // aoc
