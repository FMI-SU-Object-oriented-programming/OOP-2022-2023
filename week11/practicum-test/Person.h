#pragma once

class Person
{
public:
	Person(const char* firstName, const char* lastName, const char* UCN);
	Person(const char* firstName, const char* middleName, const char* lastName, const char* UCN);

	const char* getFirstName() const;
	const char* getMiddleName() const;
	const char* getLastName() const;
	const char* getUCN() const;

	void setFirstName(const char* name);
	void setMiddleName(const char* name);
	void setLastName(const char* name);

	bool operator ==(const Person& other) const;
	bool operator !=(const Person& other) const;

private:
	char firstName[31];
	char middleName[31];
	char lastName[31];
	char UCN[11]; // \0 for printing

	bool isNameValid(const char* name);
	bool isUCNValid(const char* UCN);
};