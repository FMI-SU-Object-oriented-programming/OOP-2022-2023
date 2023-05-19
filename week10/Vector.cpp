#include "Vector.h"

Vector::Vector(size_t dimension)
    : data(new float[dimension]), capacity(dimension)
{
}

Vector::Vector(const Vector& other)
{
    copy(other);
}

Vector& Vector::operator=(const Vector& other)
{
    if (this != &other)
    {
        free();
        copy(other);
    }
    return *this;
}

Vector::~Vector()
{
    free();
}

void Vector::free()
{
    delete[] data;
}

void Vector::copy(const Vector& other)
{
    capacity = other.capacity;
    data = new float[capacity];
    
    for (size_t i = 0; i < capacity; i++)
        data[i] = other.data[i];
}
