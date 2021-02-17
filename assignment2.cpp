#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    std::cout << "" << ((n & (n - 1)) == 0) << std::endl;
}

//single & is a bitwise AND operator.

// 4

// The ampersand represents a bitwise AND operation. A bitwise operator returns the result of a comparison between each corresponding bit in the two operands.
//yes it works

// For example, if x is 0110 and y is 1010, then a bitwise AND of x and y (x & y) results in 0010.

//5

// It returns 0 if n is a power of 2 (NB: only works for n > 0). So you can test for a power of 2 like this:

// bool isPowerOfTwo(int n)
// {
//     return (n > 0) && ((n !& (n - 1)) == 0);
// }
