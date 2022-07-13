#include "intcode/basic_vm.h"

#include "intcode/opcode.h"
#include "utility/io.h"

#include "fmt/format.h"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdint>

namespace aoc
{
	namespace intcode
	{
		Basic_vm::Basic_vm() :
			m_ip(0),
			m_state(State::READY)
		{
		}

		Basic_vm::Basic_vm(const std::vector<int64_t>& program) :
			m_ip(0),
			m_memory(program),
			m_state(State::READY)
		{
		}

		void Basic_vm::run()
		{
			if (m_state != State::READY)
				return;

			m_state = State::RUNNING;
			while (m_state == State::RUNNING)
			{
				Opcode op = Opcode(m_memory[m_ip]);
				switch (op)
				{
					case Opcode::ADD:
						m_memory[m_memory[m_ip + 3]] = m_memory[m_memory[m_ip + 1]] + m_memory[m_memory[m_ip + 2]];
						m_ip += 4;
						break;
					case Opcode::MULTIPLY:
						m_memory[m_memory[m_ip + 3]] = m_memory[m_memory[m_ip + 1]] * m_memory[m_memory[m_ip + 2]];
						m_ip += 4;
						break;
					case Opcode::HALT:
						m_state = State::HALTED;
						break;
					default:
						throw std::runtime_error(fmt::format("Unknown opcode: {}", m_memory[m_ip]));
						break;
				}
			}
		}

		State Basic_vm::state() const
		{
			return m_state;
		}

		const int64_t& Basic_vm::operator[](const size_t idx) const
		{
			return m_memory[idx];
		}

		int64_t& Basic_vm::operator[](const size_t idx)
		{
			return m_memory[idx];
		}

		std::ostream& operator<<(std::ostream& os, const Basic_vm& vm)
		{
			for (size_t i = 0; i < vm.m_memory.size(); ++i)
			{
				os << vm.m_memory[i];
				if (i < vm.m_memory.size() - 1)
				{
					os << ", ";
				}
			}

			return os;
		}

	} // aoc

} // aoc
