#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;
// primary template to compute 3 to the Nth
template <int N, int LO = 1, int HI = N>
class Sqrt
{
public:
    static int const mid = (LO + HI + 1) / 2;
    static int const result = (N < mid * mid) ? Sqrt<N, LO, mid - 1>::result : Sqrt<N, mid, HI>::result;
};

//Base Case using partial specialization
template <int N, int M>
class Sqrt<N, M, M>
{
public:
    static int const result = M;
};

int main()
{
    Sqrt<82> a;
    cout << a.result << endl;
}