#ifndef AOC_INTCODE_PROGRAM_IO_H
#define AOC_INTCODE_PROGRAM_IO_H

#include <filesystem>
#include <vector>
#include <cstdint>

namespace aoc
{
	namespace intcode {
		std::vector<int64_t> read_file(const std::filesystem::path& program_path);

	} // intcode

} // aoc

#endif // !AOC_INTCODE_PROGRAM_IO_H
