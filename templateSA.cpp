#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

template <class T>
class SA
{

private:
    int lowRow, highRow;
    T *p;

public:
    SA()
    {
        lowRow = 0;
        highRow = -1;
        p = NULL;
        cout << "defualt constructor ran: lowRow: " << lowRow << " highRow: " << highRow << endl;
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
        cout << " constructor with double args ran: lowRow: " << lowRow << " highRow: " << highRow << endl;
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
        cout << " constructor with single arg ran: lowRow: " << lowRow << " highRow: " << highRow << endl;
    }

    SA(const SA &a)
    {
        int size = a.highRow - a.lowRow + 1;
        p = new T[size];
        for (int i = 0; i < size; i++)
            p[i] = a.p[i];
        lowRow = a.lowRow;
        highRow = a.highRow;
        cout << "Copy constructor called lowRow: " << lowRow << " highRow: " << highRow << endl;
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
        cout << "Assignment Operator called lowRow: " << lowRow << " highRow: " << highRow << endl;
        return *this;
    }

    T &operator[](int i)
    {
        cout << "Overloaded [] operator called: " << lowRow << " highRow: " << highRow << endl;
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
            cout << s.p[i] << " " << endl;
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
public:
    int lowRow, highRow, lowCol, highCol;
    SA<SA<T> > p;

    Matrix()
    {
        lowRow = 0;
        highRow = -1;
        lowCol = 0;
        highCol = -1;
        cout << "defualt constructor ran: lowRow: " << lowRow << " highRow: " << highRow << endl;
    }

    Matrix(int lr, int hr, int lc, int hc)
    {
        if ((hr < lr) || (hc < hr))
        {
            cout << "constructor error in bounds definition" << endl;
            exit(1);
        }
        lowRow = lr;
        highRow = hr;
        lowCol = lc;
        highCol = hc;

        p = SA<SA<T> >(lr, hr);
        for (int i = 0; i < (hr - lr + 1); i++)
        {
            p[i] = SA<T>(lc, hc);
        }
        cout << " constructor with double args ran: lowRow: " << lowRow << " highRow: " << highRow << endl;
    }

    Matrix(int rowCapacity, int colCapacity)
    {
        if (rowCapacity < 0 || colCapacity < 0)
        {
            cout << "constructor error: Please instantiate SA of positive length" << endl;
            exit(1);
        }
        lowRow = 0;
        highRow = rowCapacity - 1;
        lowCol = 0;
        highCol = colCapacity - 1;
        p = SA<SA<T> >(lowRow, highRow);
        for (int i = 0; i < (highRow - lowRow + 1); i++)
        {
            p[i] = SA<T>(lowCol, highCol);
        }
        cout << " constructor with single arg ran: lowRow: " << lowRow << " highRow: " << highRow << endl;
    }

    Matrix<T> &operator=(const Matrix<T> &a)
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
        cout << "Assignment Operator called lowRow: " << lowRow << " highRow: " << highRow << endl;
        return *this;
    }

    SA<T> &operator[](int i)
    {
        cout << "Overloaded [] operator called: " << lowRow << " highRow: " << highRow << endl;
        if (i < lowRow || i > highRow)
        {
            cout << "index " << i << " out of range" << endl;
            exit(1);
        }
        return p[i - lowRow];
    }

    friend ostream &operator<<(ostream &os, Matrix<T> s)
    {
        int size = s.highRow - s.lowRow + 1;
        for (int i = 0; i < size; i++)
            cout << s.p[i] << endl;
        return os;
    }
};

class Multiply
{
private:
    Matrix<int> a;
    Matrix<int> b;

public:
    Multiply(Matrix<int> first, Matrix<int> second)
    {
        if ((first.highCol - first.lowCol) != (second.highRow - second.lowRow))
        {
            cout << "Matrix Multiplication only possible when number of cols of first matrix equals number of rows of the second matrix." << endl;
            exit(0);
        }
        a = first;
        b = second;
        }
};

int main()
{
    Matrix<int> m(10, 10);
    Matrix<int> n(10, 10);
    cout << m[9][9] << endl;
    cout << m << endl;
    return 0;
}