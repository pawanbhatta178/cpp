#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;
// primary template to compute 3 to the Nth
template <int N>
class Factorial
{
public:
    static int const result = N * Factorial<N - 1>::result;
};

//Complete specialization base case
template <>
class Factorial<0>
{
public:
    static int const result = 1;
};

int main()
{
    Factorial<4> a;
    cout << a.result << endl;
}