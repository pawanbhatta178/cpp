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
        cout << "defualt constructor ran: low: " << low << " high: " << high << endl;
    }

    SA(int l, int h)
    {
        if (h < l)
        {
            cout << "constructor error in bounds definition" << endl;
            exit(1);
        }
        low = l;
        high = h;
        p = new T[h - l + 1];
        cout << " constructor with double args ran: low: " << low << " high: " << high << endl;
    }

    SA(int capacity)
    {
        if (capacity < 0)
        {
            cout << "constructor error: Please instantiate SA of positive length" << endl;
            exit(1);
        }
        low = 0;
        high = capacity - 1;
        p = new T[capacity];
        cout << " constructor with single arg ran: low: " << low << " high: " << high << endl;
    }

    SA(const SA &a)
    {
        int size = a.high - a.low + 1;
        p = new T[size];
        for (int i = 0; i < size; i++)
            p[i] = a.p[i];
        low = a.low;
        high = a.high;
        cout << "Copy constructor called low: " << low << " high: " << high << endl;
    }

    SA &operator=(const SA &a)
    {
        if (this == &a)
        {
            return *this;
        }
        delete[] p;
        int size = a.high - a.low + 1;
        p = new T[size];
        for (int i = 0; i < size; i++)
            p[i] = a.p[i];
        low = a.low;
        high = a.high;
        cout << "Assignment Operator called low: " << low << " high: " << high << endl;
        return *this;
    }

    T &operator[](int i)
    {
        cout << "Overloaded [] operator called: " << low << " high: " << high << endl;
        if (i < low || i > high)
        {
            cout << "index " << i << " out of range" << endl;
            exit(1);
        }
        return p[i - low];
    }

    friend ostream &operator<<(ostream &os, SA s)
    {
        int size = s.high - s.low + 1;
        for (int i = 0; i < size; i++)
            cout << s.p[i] << endl;
        return os;
    }

    ~SA()
    {
        delete[] p;
        cout << "Destructor called " << endl;
    }
};

template <class T>
class Matrix
{
private:
    int low, high;
    SA<T> *p;

public:
    Matrix()
    {
        low = 0;
        high = -1;
        p = NULL;
    }
    Matrix(int l, int h)
    {
        if (h < l)
        {
            cout << "Matrix constructor error in bounds definition" << endl;
            exit(1);
        }
        low = l;
        high = h;
        p = new SA<T>[h - l + 1];
        cout << "Matrix constructor with double args ran: low: " << low << " high: " << high << endl;
    }

    Matrix(const Matrix &a)
    {
        int size = a.high - a.low + 1;
        p = new SA<T>[size];
        for (int i = 0; i < size; i++)
            p[i] = a.p[i];
        low = a.low;
        high = a.high;
        cout << "Matrix Copy constructor called low: " << low << " high: " << high << endl;
    }
    Matrix &operator=(const Matrix &a)
    {
        if (this == &a)
        {
            return *this;
        }
        delete[] p;
        int size = a.high - a.low + 1;
        p = new SA<T>[size];
        for (int i = 0; i < size; i++)
            p[i] = a.p[i];
        low = a.low;
        high = a.high;
        cout << "Matrix Assignment Operator called low: " << low << " high: " << high << endl;
        return *this;
    }

    SA<T> &operator[](int i)
    {
        cout << "Overloaded [] operator called: " << low << " high: " << high << endl;
        if (i < low || i > high)
        {
            cout << "index " << i << " out of range" << endl;
            exit(1);
        }
        return p[i - low];
    }

    ~Matrix()
    {
        cout << "Matrix destructor with double args ran: low: " << low << " high: " << high << endl;
        delete[] p;
    }
};

int main()
{
    SA<int> c(20);
    c[1] = 5555;
    SA<int> d = c;
    Matrix<int> e(0, 20);
    e[0] = d;
    cout << e[0] << endl;
    return 0;
}