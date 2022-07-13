#ifndef AOC_INTCODE_OPCODE_H
#define AOC_INTCODE_OPCODE_H

namespace aoc
{
	namespace intcode
	{
		enum class Opcode
		{
			ADD           = 1,
			MULTIPLY      = 2,
			INPUT         = 3,
			OUTPUT        = 4,
			JUMP_IF_TRUE  = 5,
			JUMP_IF_FALSE = 6,
			LESS_THAN     = 7,
			EQUALS        = 8,
			HALT          = 99
		};

		enum class Parameter_mode
		{
			POSITION  = 0, // Argument is a memory address to read from
			IMMEDIATE = 1  // Argument is a value
		};

		// VM state
		enum class State
		{
			READY,    // VM is ready to execute
			RUNNING,  // VM is running
			BLOCKING, // VM execution is blocked if input queue is empty
			HALTED    // VM execution has stopped
		};

	} // intcode

} // aoc

#endif // !AOC_INTCODE_OPCODE_H
