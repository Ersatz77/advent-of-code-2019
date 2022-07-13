#ifndef AOC_INTCODE_BASIC_VM_H
#define AOC_INTCODE_BASIC_VM_H

#include "intcode/opcode.h"

#include <iostream>
#include <filesystem>
#include <vector>
#include <cstdint>

namespace aoc
{
	namespace intcode
	{
		class Basic_vm
		{
		public:
			Basic_vm();
			explicit Basic_vm(const std::vector<int64_t>& program);

			void run();
			State state() const;

			const int64_t& operator[](const size_t idx) const;
			int64_t& operator[](const size_t idx);

			friend std::ostream& operator<<(std::ostream& os, const Basic_vm& vm);

		private:
			size_t m_ip;
			std::vector<int64_t> m_memory;

			State m_state;
		};

	} // intcode

} // aoc

#endif // !AOC_INTCODE_BASIC_VM_H
