#ifndef AOC_INTCODE_VM_H
#define AOC_INTCODE_VM_H

#include "intcode/opcode.h"

#include <iostream>
#include <filesystem>
#include <vector>
#include <queue>
#include <optional>
#include <cstdint>

namespace aoc
{
	namespace intcode
	{
		class Vm
		{
		public:
			Vm();
			explicit Vm(const std::vector<int64_t>& program);

			// Runs the VM
			// Execution stops if:
			//  * The input queue is empty when an input opcode is read
			//  * A value was pushed to the output queue
			//  * The VM has halted
			void run();

			void push_input(const int64_t val);
			int64_t pop_output();
			std::optional<int64_t> try_pop_output();

			size_t input_size() const;
			size_t output_size() const;

			bool has_input() const;
			bool has_output() const;
			bool is_ready() const;
			bool is_blocked() const;
			bool is_halted() const;

			const int64_t& operator[](const size_t idx) const;
			int64_t& operator[](const size_t idx);

			friend std::ostream& operator<<(std::ostream& os, const Vm& vm);

		private:
			const int64_t& read_from(const Parameter_mode mode, const size_t offset) const;
			int64_t& write_to(const Parameter_mode mode, const size_t offset);
			
			size_t m_ip;
			std::vector<int64_t> m_memory;

			std::queue<int64_t> m_stdin;
			std::queue<int64_t> m_stdout;

			State m_state;
		};

	} // intcode

} // aoc

#endif // !AOC_INTCODE_VM_H
