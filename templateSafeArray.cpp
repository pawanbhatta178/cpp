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
    int lowRow, highRow;
    int lowCol, highCol;
    SA<T> *p;

public:
    Matrix()
    {
        lowRow = 0;
        highRow = -1;
        lowCol = 0;
        highCol = 0;
        p = NULL;
    }
    Matrix(int lr, int hr, int lc, int hc)
    {
        if ((hr < lr) || (hc < lc))
        {
            cout << "Matrix constructor error in bounds definition" << endl;
            exit(1);
        }

        lowRow = lr;
        highRow = hr;
        lowCol = lc;
        highCol = hc;
        p = new SA<T>[hr - lr + 1];
        for (int i = 0; i < (hc - lc + 1); i++)
        {
            p[lowCol + i] = SA<T>(lc, hc);
        }
        cout << "Matrix constructor with double args ran: lowRow: " << lowRow << " highRow: " << highRow << endl;
    }

    Matrix(const Matrix &a)
    {
        int size = a.highRow - a.lowRow + 1;
        p = new SA<T>[size];
        for (int i = 0; i < size; i++)
            p[i] = a.p[i];
        lowRow = a.lowRow;
        highRow = a.highRow;
        cout << "Matrix Copy constructor called lowRow: " << lowRow << " highRow: " << highRow << endl;
    }

    Matrix &operator=(const Matrix &a)
    {
        if (this == &a)
        {
            return *this;
        }
        delete[] p;
        int size = a.highRow - a.lowRow + 1;
        p = new SA<T>[size];
        for (int i = 0; i < size; i++)
            p[i] = a.p[i];
        lowRow = a.lowRow;
        highRow = a.highRow;
        cout << "Matrix Assignment Operator called lowRow: " << lowRow << " highRow: " << highRow << endl;
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

    ~Matrix()
    {
        cout << "Matrix destructor with double args ran: lowRow: " << lowRow << " highRow: " << highRow << endl;
        delete[] p;
    }
};

int main()
{
    Matrix<int> e(50, 100, 0, 20);
    e[50][2] = 9999;
    cout << e[40][1] << endl;
    cout << e[40][2] << endl;

    return 0;
}