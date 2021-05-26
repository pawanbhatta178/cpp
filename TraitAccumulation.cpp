#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

template <typename T>
class AccumulationTraits;

template <>
class AccumulationTraits<char>
{
public:
    typedef int AccT;
};

template <>
class AccumulationTraits<short>
{
public:
    typedef int AccT;
};

template <>
class AccumulationTraits<int>
{
public:
    typedef long AccT;
};

template <>
class AccumulationTraits<unsigned int>
{
public:
    typedef unsigned long AccT;
};

template <>
class AccumulationTraits<float>
{
public:
    typedef double AccT;
};

template <typename T>
inline typename AccumulationTraits<T>::AccT accum(T const *beg, T const *end)
{
    // return type is traits of the element type
    typedef typename AccumulationTraits<T>::AccT AccT;
    AccT total = AccT(); // assume T() actually   creates a zero value
    while (beg != end)
    {
        total += *beg;
        ++beg;
    }
    return total;
}

int main()
{
    // create array of 5 integer values
    int num[] = {1, 2, 3, 4, 5};

    // print average value
    cout
        << "the average value of the integer values is "
        << accum(&num[0], &num[5]) / 5
        << "\n";
    // create array of character values
    char name[] = "templates";
    int length = sizeof(name) - 1;
    // (try to) print average character value
    cout << "the average value of the characters in " << name << "\" is " << accum(&name[0], &name[length]) / length << "\n";
}