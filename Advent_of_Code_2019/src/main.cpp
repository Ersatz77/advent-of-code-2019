#include "pch.h"

void day_1();
void day_2();
void day_3();
void day_4();
void day_5();
void day_6();
void day_7();
void day_8();
void day_9();
void day_10();
void day_11();
void day_12();
void day_13();
void day_14();

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
		//day_8();
		//day_9();
		//day_10();
		//day_11();
		//day_12();
		//day_13();
		day_14();
	}
	catch (const std::exception & e)
	{
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}

	return 0;
}