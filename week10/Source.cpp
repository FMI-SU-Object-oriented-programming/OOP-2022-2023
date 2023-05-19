#include <iostream>
#include "Vector2D.h"

int main()
{
	Vector2D vec1(1, 2);
	Vector2D vec2;
	vec2['x'] = 3;
	vec2['y'] = 4;
	std::cout << vec1 + vec2 << std::endl; // (4, 6)
	vec1 += vec1;	// (1, 2) + (1, 2)
	vec1();			// (2, 4)    this call is equivalent to vec1.operator()();

	try
	{
		vec1['z'] = 489; // throws invalid_argument
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}