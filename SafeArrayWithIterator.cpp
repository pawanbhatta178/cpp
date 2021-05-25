#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

template <class SA>
class SAIterator
{
public:
    typedef typename SA::ValueType ValueType;
    typedef ValueType *PointerType;
    typedef ValueType &ReferenceType;

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
    typedef T ValueType;
    typedef SAIterator<SA<T> > Iterator;
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
    SA<int> a(0, 90);

    for (int i = 2; i < 90; ++i)
    {
        a[i] = 2 * i;
    }

    int Number = 0;
    while (Number != -1)
    {
        cout << "\nEnter the element to find (-1 = end):";
        cin >> Number;
        if (Number != -1)
        {
            SA<int>::Iterator it = find(a.begin(), a.end(), Number);
            if (it != a.end())
            {
                cout << "Found it: " << *it;
            }
            else
            {
                cout << "Could not find the element";
            }
        }
    }

    return 0;
}