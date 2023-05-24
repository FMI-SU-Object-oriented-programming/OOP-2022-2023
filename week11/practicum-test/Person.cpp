#include "Person.h"

#pragma warning(disable:4996)

#include <cstring>
#include <stdexcept>

Person::Person(const char* firstName, const char* lastName, const char* UCN)
    : Person(firstName, nullptr, lastName, UCN)
{
}

Person::Person(const char* firstName, const char* middleName, const char* lastName, const char* UCN)
{
    if (!isNameValid(firstName) || !isNameValid(lastName) || !isUCNValid(UCN))
        throw std::invalid_argument("Invalid ctor parameters!");

    setFirstName(firstName);
    setMiddleName("");
    setLastName(lastName);
    strcpy(this->UCN, UCN);

    if (middleName != nullptr)
    {
        if (strlen(middleName) > 30)
            throw std::invalid_argument("Invalid ctor parameters!");

        setMiddleName(middleName);
    }
}

const char* Person::getFirstName() const
{
    return firstName;
}

const char* Person::getMiddleName() const
{
    return middleName;
}

const char* Person::getLastName() const
{
    return lastName;
}

const char* Person::getUCN() const
{
    return UCN;
}

void Person::setFirstName(const char* name)
{
    if (!isNameValid(name))
        return;

    strcpy(firstName, name);
}

void Person::setMiddleName(const char* name)
{
    if (!isNameValid(name))
        return;

    strcpy(middleName, name);
}

void Person::setLastName(const char* name)
{
    if (!isNameValid(name))
        return;

    strcpy(lastName, name);
}

bool Person::operator==(const Person& other) const
{
    return strcmp(UCN, other.UCN) == 0;
}

bool Person::operator!=(const Person& other) const
{
    return !(*this == other);
}

bool Person::isNameValid(const char* name)
{
    if (name == nullptr)
        return false;

    if (strlen(name) > 30)
        return false;

    return true;
}

bool Person::isUCNValid(const char* UCN)
{
    return UCN != nullptr && strlen(UCN) == 10;
}
