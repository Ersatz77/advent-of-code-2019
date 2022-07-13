#include "day_4/day_4.h"

#include "utility/utility.h"

#include "fmt/format.h"

#include <iostream>
#include <filesystem>
#include <array>
#include <string>
#include <algorithm>

namespace aoc
{
	constexpr int password_min = 165432;
	constexpr int password_max = 707912;

	static bool is_valid_password_p1(const std::array<int, 6> digits)
	{
		// Get digit counts
		std::array<int, 10> digit_counts = {};
		for (const int digit : digits)
		{
			++digit_counts[digit];
		}

		// Sorted, and there's 1 digit that repeats at least twice
		return std::is_sorted(digits.begin(), digits.end()) 
			&& std::any_of(digit_counts.begin(), digit_counts.end(), [](const int i) { return i >= 2; });
	}

	static bool is_valid_password_p2(const std::array<int, 6> digits)
	{
		// Get digit counts
		std::array<int, 10> digit_counts = {};
		for (const int digit : digits)
		{
			++digit_counts[digit];
		}

		// Sorted, and there's 1 digit that repeats exactly twice (So it can't be part of a larger group)
		return std::is_sorted(digits.begin(), digits.end())
			&& std::any_of(digit_counts.begin(), digit_counts.end(), [](const int i) { return i == 2; });
	}

	std::string Day_4::part_1(const std::filesystem::path&) const
	{
		int valid_passwords = 0;
		for (int password = password_min; password <= password_max; ++password)
		{
			std::array<int, 6> digits = int_to_aray<6>(password);
			if (is_valid_password_p1(digits))
			{
				++valid_passwords;
			}
		}

		return fmt::format("Valid passwords: {}", valid_passwords);
	}

	std::string Day_4::part_2(const std::filesystem::path&) const
	{
		int valid_passwords = 0;
		for (int password = password_min; password <= password_max; ++password)
		{
			std::array<int, 6> digits = int_to_aray<6>(password);
			if (is_valid_password_p2(digits))
			{
				++valid_passwords;
			}
		}

		return fmt::format("Valid passwords: {}", valid_passwords);
	}

} // aoc
