#include "pch.h"

void day_1();
void day_2();
void day_3();
void day_4();
void day_5();
void day_6();
void day_7();
void day_8();

int main()
{
	try
	{
		//day_1();
		//day_2();
		//day_3();
		//day_4();
		//day_5();
		//day_6();
		//day_7();
		day_8();
	}
	catch (const std::exception & e)
	{
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}

	return 0;
}