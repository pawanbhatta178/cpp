#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;
// primary template to compute 3 to the Nth
template <int N>
class Pow3
{
public:
    static int const result = 3 * Pow3<N - 1>::result;
};
// full specialization to end the recursion
template <>
class Pow3<0>
{
public:
    static int const result = 1;
};

int main()
{
    Pow3<2> p;
    cout << p.result << endl;
}