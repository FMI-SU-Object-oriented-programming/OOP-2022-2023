#include <iostream>
#include <cstring>

// Class declaration and method declaration
class BankAccount
{
    public:
        // Default Constructor
        BankAccount();
        // Constructor
        // We use const char[] because we are sending a pointer to an array,
        // and we want to guarantee that we won't change its content
        BankAccount(const char id[8], double balance, const char name[128]);

        // Accessors

        // Same idea. We want to return a const char array.
        // We don't want a user to change its content in any way!
        const char* getId() const;
        const char* getName() const;
        double getBalance() const;

        // In the accessors we may notice the const keyword.
        // This means that by calling a get method, we
        // guarantee that we won't change any of the class' fields!

        // Modifiers
        void setId(const char id[8]);
        void setName(const char name[128]);
        void setBalance(double balance);

        void withdrawMoney(double amount); 

        void print() const;
    private:
        char id[8];
        double balance;
        char name[128];
};

// Method definitions
// It has the following syntax:
// <return-type> <class-scope>::<class-method>(<parameters>) [const]

BankAccount::BankAccount()
    : balance(0) // Important! This is called a member initalizer list
    // The order in which the class members(fields) are assigned is determined
    // by their order of declaration inside the class!
    // The order in which we call them in the initalizer list does NOT matter.
    // So if we initalized id and name, it will first set the value for id, then for balance
    // and finally for name. It will do this no matter the order of the assignments in the list!
{
    strcpy(id, "UNKNOWN");
    strcpy(name, "UNKNOWN");
}

BankAccount::BankAccount(const char id[8], double balance, const char name[128])
{
    // We use the setters here, because we want to set valid data to our fields
    setId(id);
    setBalance(balance);
    setName(name);
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

    // 'this' is a pointer to the current instance of the class
    // this is why we call operator '->' on it, instead of the '.' operator
    // It is needed here because the field of the class is being 'shadowed'.
    // The most local variable is 'id' which is sent as a parameter to the function.
    // This means that the class field 'id' must be accessed through 'this'
    strcpy(this->id, id);
}

void BankAccount::setName(const char name[128])
{
    // Refer to the comment above for 'this'
    strcpy(this->name, name);
}

void BankAccount::setBalance(double balance)
{
    // We can not have a negative balance!
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
        // Later in the course, we might want to throw an exception here
        // and let the calling function handle the error
        std::cout << "Insufficient funds!";
        return;
    }

    // Notice how we aren't using 'this' here.
    // This is beacuse 'balance' is not being shadowed
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
    BankAccount user0;     // Valid - Calls the default constructor. If it's not user defined,
                           // then the fields are set to a random value
    BankAccount user1{};   // Valid - Calls the default constructor. If it's not user defined,
                           // then the fields are set to their default values
    BankAccount user2();     // Invalid - we are maing a function declaration and not calling a default constructor

    BankAccount ivan("AS321LK", 6.98, "Ivan Ivanov"); // Calling a constructor with parameters
    ivan.print();

    BankAccount ivanCopy = ivan;
    ivanCopy.setName("Georgi Nikolov");
    ivanCopy.setId("HG54R31");
    ivanCopy.setBalance(12.89);
    ivanCopy.print();

    // Will the objects have the same name or different names?

    std::cout << "\n\n\n";

    std::cout << "Ivan: \n";
    ivan.print();

    std::cout << "\nIvanCopy: \n";
    ivanCopy.print();

    // We do NOT need a copy constructor if we are working with
    // static arrays(arrays that are located on our stack a.k.a not dynamically allocated)
}
