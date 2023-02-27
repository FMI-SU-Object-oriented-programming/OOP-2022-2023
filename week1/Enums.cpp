#include <iostream>

using namespace std;

const char* days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
enum class Weekday
{
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

int main()
{
    cout << "The days of the week are: ";
    for (int i = 0; i < (int)Weekday::Sunday; i++)
    {
        cout << days[i] << " ";
    }

    Weekday today = Weekday::Monday; 
    cout << endl << "Today is " << days[(int)today] << endl;
    return 0;
}