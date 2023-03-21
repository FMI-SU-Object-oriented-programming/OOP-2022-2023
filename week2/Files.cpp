#include <iostream>
#include <fstream>

// using std::<type> lets me use <type>
// wihout typing std:: infront!
using std::ofstream;
using std::ifstream;

void writeFile(const char* filePath, const char* content)
{
     // Oppeining the file for writing
    ofstream outputStream(filePath);

    // Validate if the stream is in a valid state
    // and that it has oppened successfully 
    if (!outputStream || !outputStream.is_open())
    {
        std::cout << "Error opening file for writing!" << std::endl;
        return;
    }

    // File has been opened successfully!

    // Dumps all of the contents in the file
    outputStream << content;

    outputStream.close(); // Do not forget to close the stream!
}

void appendToFile(const char* filePath, const char* content)
{
    // Oppeining the file for writing while appending content
    ofstream outputStream(filePath, std::ios::app);

    // ios::in	   - Opens a file for reading
    // ios::out	   - Opens a file for writing. If the file exists then the contents are deleted.
    // ios::ate	   - Opens a file for writing while setting the stream pointer at the end of file.
    // ios::app	   - Opens a file for writing while setting the stream pointer at the enf of file. The pointer can NOT be moved!
    // ios::trunc  - If the file exists, then the conetents are deleted.	
    // ios::binary - Opens the file in binary state.

    // -------------------------------------------------------------------------------
    // NOTE! THE FOLLOWING ARE NOT IN THE C++ STANDARD! THEY SHOULDN'T BE USED!
    // ios::nocreate
    // ios::noreplace
    // -------------------------------------------------------------------------------

    // Validate if the stream is in a valid state
    // and that it has oppened successfully 
    if (!outputStream || !outputStream.is_open())
    {
        std::cout << "Error opening file for writing!" << std::endl;
        return;
    }

    // File has been opened successfully!

    // Writing a space incase the file doesn't end on one.
    outputStream << " ";

    // Dumps all of the contents in the file
    outputStream << content;

    outputStream.close(); // Do not forget to close the stream!
}

void readFile(const char* filePath)
{
    // Oppeining the file for reading
    ifstream inputStream(filePath);

    // Validate if the stream is in a valid state
    // and that it has oppened successfully 
    if (!inputStream || !inputStream.is_open())
    {
        std::cout << "Error opening file for reading!" << std::endl;
        return;
    }

    // File has been opened successfully!

    char c; // Store a character from the stream;

    // Prints all the contents of the file!
    while (!inputStream.eof() && inputStream) // Run loop while stream is valid
    {
        c = inputStream.get();
        std::cout << c;
        // We can also write std::cout << inputStream.get();
    }

    std::cout << std::endl;

    inputStream.close(); // Do not forget to close the stream!
}

int sumContents(const char* filePath)
{
    ifstream inputStream(filePath);

    // Validate if the stream is in a valid state
    // and that it has oppened successfully 
    if (!inputStream || !inputStream.is_open())
    {
        std::cout << "Error opening file for reading!" << std::endl;
        return 0;
    }

    // File has been opened successfully!

    int sum = 0; // A place to store the sums
    int currentNum; // Store the current number

    // Prints all the contents of the file!
    while (!inputStream.eof() && inputStream) // Run loop while stream is valid
    {
        inputStream >> currentNum; // Read a number from stream
        sum += currentNum;
    }

    // If stream has been invalidated, notify user!
    if (!inputStream)
    {
        std::cout << "The contents of the file are invalid!" << std::endl;
        return 0;
    }

    inputStream.close(); // Do not forget to close the stream!


    return sum;
}

int main()
{
    const char* filePath = "numbers.txt";

    //writeFile(filePath, "12h 53 23 12 99 23 23 88 992 23 12"); // Invalid

    writeFile(filePath, "12 53 23 12 99 23 23 88 992 23 12");
    readFile(filePath);

    int sum = sumContents(filePath);
    std::cout << "Sum of digits: " << sum << std::endl;

    appendToFile(filePath, "-1000");
    readFile(filePath);

    sum = sumContents(filePath);
    std::cout << "Sum of digits: " << sum << std::endl;
}