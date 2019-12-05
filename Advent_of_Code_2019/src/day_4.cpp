#include "pch.h"

void day_4()
{
	constexpr int range_min = 165432;
	constexpr int range_max = 707912;

	int part_1_valid_passwords = 0;
	int part_2_valid_passwords = 0;

	for (int i = range_min; i <= range_max; ++i)
	{
		// Store digits into vector
		std::vector<int> digits;
		for (const char& c : std::to_string(i))
		{
			digits.push_back(std::stoi(std::to_string(c)));
		}

		// Check if digits are in increasing order
		if (std::is_sorted(digits.begin(), digits.end()))
		{
			// Part 1			
			for (int j = 0; j < digits.size() - 1; ++j)
			{
				if (digits[j] == digits[j + 1])
				{
					++part_1_valid_passwords;
					break;
				}
			}

			// Part 2
			std::vector<int> unique_digits = digits;
			for (const int& k : digits)
			{
				int matches = std::count(digits.begin(), digits.end(), k);
				if (matches != 2)
				{
					unique_digits.erase(std::remove(unique_digits.begin(), unique_digits.end(), k), unique_digits.end());
				}
			}

			if (unique_digits.size() != 0 && unique_digits.size() % 2 == 0)
			{
				std::cout << i << '\n';
				++part_2_valid_passwords;
			}
			
			
			
		}
	}

	std::cout << "Part 1 valid passwords: " << part_1_valid_passwords << '\n';
	std::cout << "Part 2 valid passwords: " << part_2_valid_passwords << '\n';
}