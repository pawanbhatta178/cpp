#include <iostream>
#include <cstdarg>
using namespace std;

// Base case for recursion
template <class T>
T sum(T n)
{
    return n;
}

// Recursive case
template <class T, class... Args>
T sum(T n, Args... args)
{
    return n + sum(args...);
}

int main()
{
    cout << "[Summing 3 numbers: 1, 2, 3] -> " << sum(1, 2, 3) << endl;
    cout << "[Summing 2 numbers: 10,20] -> " << sum(10, 20) << endl;
    cout << "[Summing 5 numbers: 1, 2, 3,4, 5] -> " << sum(1, 2, 3, 4, 5) << endl;
}