#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

template <class T>
class SA
{

private:
    int low, high;
    T *p;

public:
    SA()
    {
        low = 0;
        high = -1;
        p = NULL;
    }

    SA(int l, int h)
    {
        if ()
            low = l;
        high = h;
        p = new T[h - l + 1];
    }
};