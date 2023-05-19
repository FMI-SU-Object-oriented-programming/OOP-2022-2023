#include <iostream>

using namespace std;

struct Drinks
{
    char data;
    /*
        'data' is 8 bits (1 byte)
        the first 3 bits will be unused
        the last 5 bits will be used to store the drinks (1 bit per drink)
        the drinks are as follows:
            - water   -> 0b00000001
            - juice   -> 0b00000010
            - beer    -> 0b00000100
            - wine    -> 0b00001000
            - whiskey -> 0b00010000
    */
};

int main()
{
    Drinks exotica;
    exotica.data = 0b00001011; // exotica serves water, juice and wine

    Drinks ivan, petar;
    ivan.data  = 0b00000101; // ivan likes water and beer
    petar.data = 0b00010010; // petar likes juice and whiskey

    // ===================================================================== //
    // Ivan is pretentious and wants the bar to serve all the drinks he likes
    
    // Petar is chill and doesn't mind the bar as long as it serves
    // at least one of the drinks he likes
    
    // Check both Ivan and Petar's preferences
    if ((ivan.data & exotica.data) == ivan.data) // 0b00000001 == 0b00000101 -> false
        cout << "Ivan is happy" << endl;
    else
        cout << "Ivan is not happy" << endl;

    if (petar.data & exotica.data) // 0b00000010 -> true
        cout << "Petar is happy" << endl;
    else
        cout << "Petar is not happy" << endl;

    // ===================================================================== //
    // After heavy drinking, Ivan decides to become a better person
    // and only wants to drink water and juice

    // remove beer, wine and whiskey from ivan's preferences
    ivan.data &= ~0b00000100;
    ivan.data &= ~0b00001000;
    ivan.data &= ~0b00010000;
    // explanation:
    // ivan.data               = 0b00000101 -> likes water and beer
    // ~0b00000100(beer)       = 0b11111011 
    // 0b00000101 & 0b11111011 = 0b00000001 -> likes water only

    // add juice to ivan's preferences
    ivan.data |= 0b00000010;
    
    // ===================================================================== //
    // Peter only drinks whiskey on the weekends

    // On mondays, we have to switch off the whiskey bit
    petar.data ^= 0b00010000;

    // On the weekends we have to switch it back on (same operation)
    petar.data ^= 0b00010000;
    
    // A different way to do this is:
    petar.data = petar.data ^ (1 << 4);
    // or shorter:
    petar.data ^= 1 << 4;

    return 0;
}