#include <iostream>
#include <cstdlib>
#include <cassert>
#include <ctime>
using namespace std;

template <class SA>
class SAIterator
{
public:
    using ValueType = typename SA::ValueType;
    using PointerType = ValueType *;
    using ReferenceType = ValueType &;

    SAIterator(PointerType ptr) : m_Ptr(ptr){};

    SAIterator &operator++()
    {
        m_Ptr++;
        return *this;
    }

    SAIterator operator++(int)
    {
        SAIterator iterator = *this;
        ++(*this);
        return iterator;
    }

    SAIterator &operator--()
    {
        m_Ptr--;
        return *this;
    }

    SAIterator operator--(int)
    {
        SAIterator iterator = *this;
        --(*this);
        return iterator;
    }

    ReferenceType operator[](int index)
    {
        return *(m_Ptr[index]);
    }

    PointerType operator->()
    {
        return m_Ptr;
    }

    ReferenceType operator*()
    {
        return *m_Ptr;
    }

    bool operator==(const SAIterator &other) const
    {
        return m_Ptr == other.m_Ptr;
    }
    bool operator!=(const SAIterator &other) const
    {
        return !(*this == other);
    }

private:
    PointerType m_Ptr;
};

template <class T>
class SA
{

private:
    int lowRow, highRow;
    T *p;

public:
    using ValueType = T;
    using Iterator = SAIterator<SA<T> >;
    SA()
    {
        lowRow = 0;
        highRow = -1;
        p = NULL;
    }

    SA(int l, int h)
    {
        if (h < l)
        {
            cout << "constructor error in bounds definition" << endl;
            exit(1);
        }
        lowRow = l;
        highRow = h;
        p = new T[h - l + 1];
    }

    SA(int capacity)
    {
        if (capacity < 0)
        {
            cout << "constructor error: Please instantiate SA of positive length" << endl;
            exit(1);
        }
        lowRow = 0;
        highRow = capacity - 1;
        p = new T[capacity];
    }

    SA(const SA &a)
    {
        int size = a.highRow - a.lowRow + 1;
        p = new T[size];
        for (int i = 0; i < size; i++)
            p[i] = a.p[i];
        lowRow = a.lowRow;
        highRow = a.highRow;
    }

    SA &operator=(const SA &a)
    {
        if (this == &a)
        {
            return *this;
        }
        delete[] p;
        int size = a.highRow - a.lowRow + 1;
        p = new T[size];
        for (int i = 0; i < size; i++)
            p[i] = a.p[i];
        lowRow = a.lowRow;
        highRow = a.highRow;
        return *this;
    }

    T &operator[](int i)
    {
        if (i < lowRow || i > highRow)
        {
            cout << "index " << i << " out of range" << endl;
            exit(1);
        }
        return p[i - lowRow];
    }

    friend ostream &operator<<(ostream &os, SA s)
    {
        int size = s.highRow - s.lowRow + 1;
        for (int i = 0; i < size; i++)
            cout << s.p[i] << " ";
        return os;
    }

    Iterator begin()
    {
        return Iterator(p);
    }

    Iterator end()
    {
        return Iterator(p + highRow - lowRow);
    }

    ~SA()
    {
        delete[] p;
    }
};

int main()
{
    SA<int> a(2, 90);
    a[2] = 89;
    for (int value : a)
    {
        cout << value << endl;
    }

    srand(time(0)); // Initialize random number generator.

    return 0;
}