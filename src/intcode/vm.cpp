#include "intcode/vm.h"

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
		Vm::Vm() :
			m_ip(0),
			m_state(State::READY)
		{
		}

		Vm::Vm(const std::vector<int64_t>& program) :
			m_ip(0),
			m_memory(program),
			m_state(State::READY)
		{
		}

		const int64_t& Vm::read_from(const Parameter_mode mode, const size_t offset) const
		{
			switch (mode)
			{
				case Parameter_mode::POSITION:
					return m_memory[m_memory[m_ip + offset]];
				case Parameter_mode::IMMEDIATE:
					return m_memory[m_ip + offset];
				default:
					throw std::invalid_argument(fmt::format("Unknown parameter mode: {} | Pointer: {}", static_cast<int>(mode), m_ip));
			}
		}

		int64_t& Vm::write_to(const Parameter_mode mode, const size_t offset)
		{
			switch (mode)
			{
				case Parameter_mode::POSITION:
					return m_memory[m_memory[m_ip + offset]];
				case Parameter_mode::IMMEDIATE:
					throw std::invalid_argument(fmt::format("Writing to memory using immediate mode is not allowed | Pointer: {}", static_cast<int>(mode), m_ip));
				default:
					throw std::invalid_argument(fmt::format("Unknown parameter mode: {} | Pointer: {}", static_cast<int>(mode), m_ip));
			}
		}

		void Vm::run()
		{
			// Only enter run state if VM is in the ready state
			if (m_state != State::READY)
				return;

			// Run program
			m_state = State::RUNNING;
			while (m_state == State::RUNNING)
			{
				// Break instruction down into its parts
				int64_t instruction = m_memory[m_ip];
				Opcode op = Opcode(instruction % 100);
				Parameter_mode param_1_mode = Parameter_mode((instruction / 100) % 10);
				Parameter_mode param_2_mode = Parameter_mode((instruction / 1000) % 10);
				Parameter_mode param_3_mode = Parameter_mode((instruction / 10000) % 10);

				// Process instruction
				switch (op)
				{
					case Opcode::ADD:
						write_to(param_3_mode, 3) = read_from(param_1_mode, 1) + read_from(param_2_mode, 2);
						m_ip += 4;
						break;
					case Opcode::MULTIPLY:
						write_to(param_3_mode, 3) = read_from(param_1_mode, 1) * read_from(param_2_mode, 2);
						m_ip += 4;
						break;
					case Opcode::INPUT:
					{
						if (m_stdin.empty())
						{
							m_state = State::BLOCKING;
							return;
						}

						write_to(param_1_mode, 1) = m_stdin.front();
						m_stdin.pop();
						m_ip += 2;
						break;
					}
					case Opcode::OUTPUT:
					{
						m_stdout.push(read_from(param_1_mode, 1));
						m_ip += 2;
						m_state = State::READY;
						return;
					}
					case Opcode::JUMP_IF_TRUE:
						m_ip = read_from(param_1_mode, 1) != 0 ? read_from(param_2_mode, 2) : m_ip + 3;
						break;
					case Opcode::JUMP_IF_FALSE:
						m_ip = read_from(param_1_mode, 1) == 0 ? read_from(param_2_mode, 2) : m_ip + 3;
						break;
					case Opcode::LESS_THAN:
						write_to(param_3_mode, 3) = read_from(param_1_mode, 1) < read_from(param_2_mode, 2) ? 1 : 0;
						m_ip += 4;
						break;
					case Opcode::EQUALS:
						write_to(param_3_mode, 3) = read_from(param_1_mode, 1) == read_from(param_2_mode, 2) ? 1 : 0;
						m_ip += 4;
						break;
					case Opcode::HALT:
						m_state = State::HALTED;
						return;
					default:
						throw std::runtime_error(fmt::format("Unknown opcode: {} | Pointer: {}", m_memory[m_ip], m_ip));
				}
			}
		}

		void Vm::push_input(const int64_t val)
		{
			if (m_state == State::BLOCKING)
				m_state = State::READY;

			m_stdin.push(val);
		}

		int64_t Vm::pop_output()
		{
			int64_t temp = m_stdout.front();
			m_stdout.pop();
			return temp;
		}

		std::optional<int64_t> Vm::try_pop_output()
		{
			if (!has_output())
				return std::nullopt;

			return pop_output();
		}

		size_t Vm::input_size() const
		{
			return m_stdin.size();
		}

		size_t Vm::output_size() const
		{
			return m_stdout.size();
		}

		bool Vm::has_input() const
		{
			return !m_stdin.empty();
		}

		bool Vm::has_output() const
		{
			return !m_stdout.empty();
		}

		bool Vm::is_ready() const
		{
			return m_state == State::READY;
		}

		bool Vm::is_blocked() const
		{
			return m_state == State::BLOCKING;
		}

		bool Vm::is_halted() const
		{
			return m_state == State::HALTED;
		}

		const int64_t& Vm::operator[](const size_t idx) const
		{
			return m_memory[idx];
		}

		int64_t& Vm::operator[](const size_t idx)
		{
			return m_memory[idx];
		}

		std::ostream& operator<<(std::ostream& os, const Vm& vm)
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

	} // intcode

} // aoc
