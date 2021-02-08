#include <iostream>
#include <cstdarg>
using namespace std;

// Base case for recursion
template <class T>
inline T sum(T n)
{
    return n;
}

// Recursive case
template <class T, class... Args>
inline T sum(T n, Args... args)
{
    return n + sum(args...);
}

int main()
{
    string string1 = "Thuis ";
    string string2 = " concatenation ";
    string string3 = " works";

    cout << "[Summing 4 numbers: 3, 44, 55, 66] -> " << sum(1, 2, 2, 3) << endl;
}