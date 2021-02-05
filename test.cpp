#include <iostream>
#include <cstdarg>
using namespace std;

// Base case for recursion
template <typename T>
inline T sum(T n)
{
    return n;
}

// Recursive case
template <typename T, typename... Args>
inline T sum(T n, Args... args)
{
    return n + sum(args...);
}

int main()
{
    cout << "[Summing 4 numbers: 3, 44, 55, 66] -> " << sum(3, 44, 55, 66) << endl;
}