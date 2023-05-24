#include "Group.h"

#include <cstring>
#include <stdexcept>

Group::Group()
	: Group(2)
{

}

Group::Group(unsigned capacity)
	: capacity(capacity), size(0), people(new Person*[capacity] {})
{

}

Group::Group(const Group& other)
{
	copy(other);
}

Group::~Group()
{
	free();
}

Group& Group::operator=(const Group& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}

	return *this;
}

Group& Group::operator+=(const Person& other) 
{
	if (size >= capacity)
		resize(capacity * 1.5f);
	
	if (!this->operator()(other))
	{
		people[size] = new Person(other);
		size++;
	}

	return *this;
}

Group Group::operator+(const Person& other) const 
{
	Group group(*this);
	return group += other;
}

Group& Group::operator-=(const Person& other)
{
	if (size <= 0)
		return *this;

	int i;
	for (i = 0; i < size; i++)
	{
		if (*people[i] == other)
			break;
	}

	if (i >= size)
		return *this;

	std::swap(people[i], people[size - 1]);

	delete people[size - 1];
	people[size - 1] = nullptr;
	size--;

	return *this;
}

Group Group::operator-(const Person& other) const 
{
	Group group(*this);
	return group -= other;
}

Person& Group::operator[](const char* UCN)
{
	for (int i = 0; i < size; i++)
	{
		if (strcmp(people[i]->getUCN(), UCN) == 0)
			return *people[i];
	}

	throw std::invalid_argument("No such person!");
}

const Person& Group::operator[](const char* UCN) const
{
	for (int i = 0; i < size; i++)
	{
		if (strcmp(people[i]->getUCN(), UCN) == 0)
			return *people[i];
	}

	throw std::invalid_argument("No such person!");
}

int Group::operator()() const
{
	return size;
}

bool Group::operator()(const Person& person) const
{
	for (int i = 0; i < size; i++)
	{
		if (*people[i] == person)
			return true;
	}

	return false;
}

int Group::getSize() const
{
	return this->operator()();
}

void Group::free()
{
	for (int i = 0; i < size; i++)
		delete people[i];

	delete[] people;
}

void Group::copy(const Group& other)
{
	size = other.size;
	capacity = other.capacity;

	people = new Person*[capacity];
	for (int i = 0; i < size && i < capacity; i++)
		people[i] = new Person(*other.people[i]);
}

void Group::resize(unsigned newCapacity)
{
	if (capacity >= newCapacity)
		return;

	Person** newPeople = new Person*[newCapacity] {};

	capacity = newCapacity;
	for (int i = 0; i < size; i++)
		newPeople[i] = people[i];

	delete[] people;
	people = newPeople;
}