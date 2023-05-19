#pragma once

class Vector
{
public:
	Vector() = delete;	// deleting the default ctor
						// because we want a vector's dimension to be specifically defined
						// upon construction
	Vector(size_t dimension);
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	~Vector();

protected:
	float* data;

private:
	size_t capacity;

	void free();
	void copy(const Vector& other);
};