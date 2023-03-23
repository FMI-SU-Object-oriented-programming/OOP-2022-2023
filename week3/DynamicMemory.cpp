#include <iostream>
#include <fstream>
#include <cstring>

using std::ifstream;
using std::ofstream;

struct Person
{
    unsigned age;
    double balance;
    char *name;
};

// Rule of thumb: If the object is bigger than 16 byte, always pass it by reference
// unless you want to edit it as a copy inside the function
void writePerson(const char* filePath, const Person& person)
{
    // Open the file for binary writing
    ofstream outputStream(filePath, std::ios::binary);

    // Validate if the stream is in a valid state
    // and that it has oppened successfully
    if (!outputStream || !outputStream.is_open())
    {
        std::cout << "Error opening file for writing!" << std::endl;
        return;
    }

    // We must write each property of Person on each own!

    outputStream.write(reinterpret_cast<const char*>(&person.age), sizeof(int));
    outputStream.write(reinterpret_cast<const char*>(&person.balance), sizeof(double));

    // We need to first write the size of the dynamically allocated string.
    // So that we can know how many characters to read afterwards.
    int nameLength = strlen(person.name);
    outputStream.write(reinterpret_cast<const char*>(&nameLength), sizeof(int));

    // Now we can write the dynamcally allocated array!
    outputStream.write(reinterpret_cast<const char*>(person.name), nameLength);

    outputStream.close();
}

Person readPerson(const char *filePath)
{
    // Open the file for binary reading
    ifstream inputStream(filePath, std::ios::binary);

    // Validate if the stream is in a valid state
    // and that it has oppened successfully
    if (!inputStream || !inputStream.is_open())
    {
        std::cout << "Error opening file for reading!" << std::endl;
        return Person{};
    }

    Person readPerson;

    // We need to read each property of Person!
    // Notice that we follow the order of writing!
    inputStream.read(reinterpret_cast<char*>(&readPerson.age), sizeof(int));
    inputStream.read(reinterpret_cast<char*>(&readPerson.balance), sizeof(double));

    // We need to get the name's length!
    int nameLength;
    inputStream.read(reinterpret_cast<char*>(&nameLength), sizeof(int));

    // And allocate dynamic memory for it!
    readPerson.name = new char[nameLength + 1]; // Plus 1 for \0
    inputStream.read(reinterpret_cast<char*>(readPerson.name), nameLength);

    // Do not forget the \0
    readPerson.name[nameLength] = '\0';

    inputStream.close();

    return readPerson;
}

// We can easily count how many Persons are stored in the file
// This only works if the size of the structure(class) is
// a constant size.(Does not have any dynamically stored memory)
int main()
{
    char* name = new char[5];
    strcpy(name, "Ivan");

    Person ivan{18, 12.50, name};

    writePerson("person.bin", ivan);

    Person person = readPerson("person.bin");

    std::cout << person.age << " " << person.balance << " " << person.name << std::endl;

    delete[] ivan.name;
    delete[] person.name;
}