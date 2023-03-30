#include <iostream>
#include <cstring>
#pragma warning(disable:4996)

// We are going to use the class from the last document
// Refer to it for details on constructors, methods, 'this' and shadowing!
class BankAccount
{
    // The big four consists of:
    // - Constructor
    // - Copy constructor
    // - Copy-assignment operator
    // - Destructor
    public:
        // Constructors
        BankAccount();
        BankAccount(const char id[8], double balance, const char* name);

        // Copy constructor
        // It has the following syntax: <class-name>(const <class-name>& {some_name})
        // It must be defined if we are working with dynamically allocated fields
        BankAccount(const BankAccount& other);

        // Destructor
        // It gets called when the created instance(object) 
        // of the class gets out of scope or gets deleted
        // It has the following syntax: ~<class-name>()
        // It must be defined if we are working with dynamically allocated fields
        ~BankAccount();

        // Copy-assignment operator
        // It has the following syntax: <class-name>& operator=(const <class-name>& {some_name})
        // It must be defined if we have a copy constructor
        BankAccount& operator=(const BankAccount& other);

        // Accessors
        const char* getId() const;
        const char* getName() const;
        double getBalance() const;

        // Modifiers
        void setId(const char id[8]);
        void setName(const char* name);
        void setBalance(double balance);

        void withdrawMoney(double amount); 

        void print() const;
    private:
        char id[8];
        double balance;
        char* name;
};

BankAccount::BankAccount()
    : balance(0), name(nullptr)
{
    setName("DEFAULT_NAME");
    strcpy(id, "UNKNOWN");
}

BankAccount::BankAccount(const char id[8], double balance, const char* name)
    : name(nullptr)
{
    setId(id);
    setBalance(balance);
    setName(name);
}

BankAccount::BankAccount(const BankAccount& other)
    : balance(other.balance)
{
    strcpy(id, other.id);

    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
}

BankAccount::~BankAccount()
{
    delete[] name;
}

BankAccount& BankAccount::operator=(const BankAccount& other)
{
    // We must check if we aren't assigning an object to itself.
    // If we assign an object to itself, we will delete its allocated dynamic memory,
    // meaning we will attempt to copy from memory that doesn't exist
    if (this != &other)
    {
        strcpy(id, other.id);
        balance = other.balance;
        
        delete[] name;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);    
    }

    return *this;
}

const char* BankAccount::getId() const
{
    return id;
}

const char* BankAccount::getName() const
{
    return name;
}

double BankAccount::getBalance() const
{
    return balance;
}

void BankAccount::setId(const char id[8])
{
    // We want to validate id. It should be exactly 7 characters (+1 for '\0)
    if (strlen(id) != 7)
    {
        // Later in the course, we might want to throw an exception here
        // and let the calling function handle the error
        std::cout << "Invalid id! Id set to 'INVALID'";
        strcpy(this->id, "INVALID");
        return;
    }

    strcpy(this->id, id);
}

void BankAccount::setName(const char* name)
{
    // We need to make sure the passed name is valid
    if(name == nullptr)
        return;

    if (this->name != nullptr)
        delete[] this->name;

    this->name = new char[strlen(name) + 1]; // + 1 for '\0'
    strcpy(this->name, name);                // '\0' gets copied over
}

void BankAccount::setBalance(double balance)
{
    if (balance <= 0)
    {
        this->balance = 0;
        return;
    }

    this->balance = balance;
}

void BankAccount::withdrawMoney(double amount)
{
    if (balance < amount)
    {
        // We might want to throw an exception here,
        // and let the calling function handle the error
        std::cout << "Insufficient funds!";
        return;
    }

    balance -= amount;
} 

void BankAccount::print() const
{
    std::cout << "Id: " << id << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Balance: " << balance << std::endl;
}

int main()
{
    BankAccount ivan("AS321LK", 6.98, "Ivan Ivanov"); // Calling a constructor with parameters
    ivan.print();

    BankAccount ivanCopy = ivan;        // Copy constructor is called! This is because a value is set during object creation
    ivanCopy.setName("Georgi Nikolov");
    ivanCopy.setId("HG54R31");
    ivanCopy.setBalance(12.89);
    ivanCopy.print();

    BankAccount copyAssignment;
    copyAssignment = ivan;              // Copy-assignemnt operator is called, because 'copyAssignemnt' already exists
                                        // and it doesn't need to be constructed!

    // Will the objects have the same name or different names?

    std::cout << "\n\n\n";

    std::cout << "Ivan: \n";
    ivan.print();

    std::cout << "\nIvanCopy: \n";
    ivanCopy.print();

    // Some questions to think about
    // How about if we remove the copy constructor?
    // Why do we get some random characters for the name in one of the objects if we remove the copy constructors?
    // Why do we need a destructor?
}
