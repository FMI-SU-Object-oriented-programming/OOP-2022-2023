#include <iostream>

using namespace std;

void map(int* arr, int size, int (*mappingFunction)(int))
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = mappingFunction(arr[i]);
    }
}

int timesTwo(int x)
{
    return x * 2;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5};

    //lambda function
    map(a, 5, [](int x) { return x * 2; });

    //function pointer
    map(a, 5, timesTwo);

    for (int i = 0; i < 5; i++)
    {
        cout << a[i] << " ";
    }

    return 0;
}