#pragma once
#include "Vector.h"
#include <iostream> // including <iostream> so we can use 'ostream' and 'istream'
					// in this header file

class Vector2D : public Vector
{
public:
	Vector2D();
	Vector2D(float x, float y);

	/*
		Since Vector2D doesn't have any dynamic fields (or any fields for
		that matter), we don't need to write the Big Four
	*/

	float& operator[](char dimension);
	float operator[](char dimension) const;
	
	void operator()() const; // We'll use this as an example for printing 
							 // (not advised in the real world)

	Vector2D& operator+=(const Vector2D& other);
	Vector2D& operator-=(const Vector2D& other);

	/*
		Alternative to ostream& operator<<

		friend std::ostream& operator<<(std::ostream& o, const Vector2D vector)
		{
			o << "(" << vector.data[0] << ", " << vector.data[1] << ")";
			return o;
		}
	*/
};

Vector2D operator+(const Vector2D& left, const Vector2D& right);
Vector2D operator-(const Vector2D& left, const Vector2D& right);

std::ostream& operator<<(std::ostream& o, const Vector2D& vector);
std::istream& operator>>(std::istream& i, Vector2D& vector);