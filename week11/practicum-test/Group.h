#pragma once

#include "Person.h"

class Group
{
public:
	Group();
	Group(unsigned capacity);
	Group(const Group& other);
	~Group();

	Group& operator=(const Group& other);

	Group& operator+=(const Person& other);
	Group operator+(const Person& other) const;

	Group& operator-=(const Person& other);
	Group operator-(const Person& other) const;

	Person& operator[](const char* UCN);
	const Person& operator[](const char* UCN) const;

	int operator()() const;
	bool operator()(const Person& person) const;

	int getSize() const;

private:
	unsigned size;
	unsigned capacity;
	Person** people;

	void free();
	void copy(const Group& other);
	void resize(unsigned newCapacity);
};