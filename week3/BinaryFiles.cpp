#include <iostream>
#include <fstream>

using std::ofstream;
using std::ifstream;

struct Person
{
    unsigned age;
    double balance;
    char name[28];
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

    // Writes the object's data into the file. We can also use
    // (const char*)&person, but using reinterpret_cast is clearer
    // and faster! (const char*) is a C-style cast, while
    // reinterpret_cast<const char*> is a C++-style cast.

    // NOTE: The padding of the structure is also being written
    outputStream.write(reinterpret_cast<const char*>(&person), sizeof(Person));

    outputStream.close();
}

void appendPerson(const char* filePath, const Person& person)
{
        // Open the file for binary writing
    ofstream outputStream(filePath, std::ios::binary | std::ios::app);

    // Validate if the stream is in a valid state
    // and that it has oppened successfully 
    if (!outputStream || !outputStream.is_open())
    {
        std::cout << "Error opening file for writing!" << std::endl;
        return;
    }

    // Writes the object's data into the file. We can also use
    // (const char*)&person, but using reinterpret_cast is clearer
    // and faster! (const char*) is a C-style cast, while
    // reinterpret_cast<const char*> is a C++-style cast.
    outputStream.write(reinterpret_cast<const char*>(&person), sizeof(Person));

    outputStream.close();
}

Person readPerson(const char* filePath)
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
    inputStream.read(reinterpret_cast<char*>(&readPerson), sizeof(Person));

    inputStream.close();

    return readPerson;
}

// We can easily count how many Persons are stored in the file
// This only works if the size of the structure(class) is
// a constant size.(Does not have any dynamically stored memory)
int countPersons(const char* filePath)
{
        // Open the file for binary reading
    ifstream inputStream(filePath, std::ios::binary);

    // Validate if the stream is in a valid state
    // and that it has oppened successfully 
    if (!inputStream || !inputStream.is_open())
    {
        std::cout << "Error opening file for reading!" << std::endl;
        return 0;
    }

    inputStream.seekg(0, std::ios::end);
    int streamPtr = inputStream.tellg();

    int count = streamPtr / sizeof(Person);

    inputStream.close();

    return count;
}

int main()
{
    Person ivan { 18, 12.50, "Ivan" };

    writePerson("person.txt", ivan);

    Person person = readPerson("person.txt");

    std::cout << person.age << " " << person.balance << " " << person.name << std::endl;

    for (int i = 0; i < 20; i++)
    {
        appendPerson("person.txt", person);
    }
    
    std::cout << countPersons("person.txt") << std::endl;
}