#include "intcode/program_io.h"

#include "utility/io.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstdint>

namespace aoc
{
	namespace intcode {
		std::vector<int64_t> read_file(const std::filesystem::path& program_path)
		{
			std::ifstream program_file = open_file(program_path);

			std::vector<int64_t> program;
			std::string temp;
			int64_t instruction = 0;
			while (std::getline(program_file, temp, ','))
			{
				std::istringstream iss(temp);
				iss >> instruction;
				program.push_back(instruction);
			}

			return program;
		}

	} // intcode

} // aoc
