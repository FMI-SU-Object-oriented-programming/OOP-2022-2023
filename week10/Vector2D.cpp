#include "Vector2D.h"
#include <stdexcept>

Vector2D::Vector2D()
	: Vector2D(0.f, 0.f)
{
}

Vector2D::Vector2D(float x, float y)
	: Vector(2) // We can't call the default ctor of Vector, because
				// it is deleted.
{
	data[0] = x;
	data[1] = y;
}

float& Vector2D::operator[](char dimension)
{
	switch (dimension)
	{
	case 'x':
	case 'X':
		return data[0];
	
	case 'y':
	case 'Y':
		return data[1];

	default:
		throw std::invalid_argument("A Vector2D can only be indexed by 'x'/'y' but a different index was given");
	}
}

float Vector2D::operator[](char dimension) const
{
	switch (dimension)
	{
	case 'x':
	case 'X':
		return data[0];

	case 'y':
	case 'Y':
		return data[1];

	default:
		throw std::invalid_argument("A Vector2D can only be indexed by 'x'/'y' but a different index was given");
	}

}



void Vector2D::operator()() const
{
	std::cout << "(" << data[0] << ", " << data[1] << ")\n";
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
	*this = *this + other;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other)
{
	*this = *this - other;
	return *this;
}




float operator~(const Vector2D& vector)
{
	return (vector['x'] + vector['y']) / 2.f;
}

Vector2D operator+(const Vector2D& left, const Vector2D& right)
{
	return Vector2D(left['x'] + right['x'], left['y'] + right['y']);
}

Vector2D operator-(const Vector2D& left, const Vector2D& right)
{
	return Vector2D(left['x'] - right['x'], left['y'] - right['y']);
}

std::ostream& operator<<(std::ostream& o, const Vector2D& vector)
{
	o << "(" << vector['x'] << ", " << vector['y'] << ")";
	return o;
}

std::istream& operator>>(std::istream& i, Vector2D& vector)
{
	i >> vector['x'] >> vector['y'];
	return i;
}
