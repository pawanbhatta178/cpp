#include <iostream>
#include <cstdlib>
#include <cassert>
#include <ctime>
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

    ~SA()
    {
        delete[] p;
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
        return *this;
    }

    SA<T> &operator[](int i)
    {
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
        cout << endl;
        for (int i = 0; i < size; i++)
            cout << s.p[i] << endl;
        return os;
    }
};

Matrix<int> Multiply(Matrix<int> first, Matrix<int> second)
{
    if ((first.highCol - first.lowCol) != (second.highRow - second.lowRow))
    {
        cout << "Matrix Multiplication only possible when number of cols of first matrix equals number of rows of the second matrix." << endl;
        exit(0);
    }
    Matrix<int> ans(first.highRow - first.lowRow + 1, second.highCol - second.lowCol + 1);
    for (int i = 0; i < first.highRow - first.lowRow + 1; i++)
    {
        for (int j = 0; j < second.highCol - second.lowCol + 1; j++)
        {
            ans[i][j] = 0;
            for (int k = 0; k < first.highCol - first.lowCol + 1; k++)
                ans[i][j] += first[i][k] * second[k][j];
        }
    }
    return ans;
}

int main()
{
    Matrix<int> m(3, 3);
    Matrix<int> n(3, 2);

    srand(time(0)); // Initialize random number generator.

    //initializing 1st safe matrix, changing max value of i and j will change the matrix size.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m[i][j] = (rand() % 10);
        }
    }

    //initializing 2nd safe matrix, changing max value of i and j will change the matrix size.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            n[i][j] = (rand() % 10);
        }
    }

    cout << m << " X " << n << endl;
    cout << "=" << endl;
    cout << Multiply(m, n) << endl;
    return 0;
}