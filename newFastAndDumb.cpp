#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

template <class T>
class SA
{
private:
    static SA<T> *newList;
    SA<T> *freepointer;
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

    //copy constructor
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
            cout << "SA [] called" << endl;

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

    void *operator new(size_t size)
    {
        if (size != sizeof(SA))
        {
            return malloc(size);
        }
        else if (!newList)
        {
            newList = (SA<T> *)new char[100 * sizeof(SA)];
            int i;
            for (i = 0; i < 99; i++)
            {
                newList[i].freepointer = &(newList[i + 1]);
            }
            newList[i].freepointer = 0;
        }
        SA<T> *savenew = newList;
        newList = newList->freepointer;
        return savenew;
    }

    void operator delete(void *ptr)
    {
        cout << "Delete Operator called" << endl;
        SA *s = (SA *)ptr;
        s->freepointer = newList;
        newList = s;
    }

    ~SA()
    {
        delete[] p;
    }
};

template <class T>
SA<T> *SA<T>::newList = 0;

template <class T>
class Matrix
{
public:
    int lowRow, highRow, lowCol, highCol;
    SA<SA<T> > *p;

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

        p = new SA<SA<T> >(lr, hr);
        for (int i = 0; i < (hr - lr + 1); i++)
        {
            (*p)[i] = SA<T>(lc, hc);
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
        p = new SA<SA<T> >(lowRow, highRow);
        for (int i = 0; i < (highRow - lowRow + 1); i++)
        {
            (*p)[i] = SA<T>(lowCol, highCol);
        }
    }

    Matrix(const Matrix &m)
    {
        lowRow = m.lowRow;
        highRow = m.highRow;
        lowCol = m.lowCol;
        highCol = m.highCol;
        p = (SA<SA<T> > *)malloc(sizeof(SA<SA<T> >));
        memmove(p, m.p, sizeof(SA<SA<T> >));
    }

    Matrix(Matrix &&m)
    {
        lowRow = m.lowRow;
        highRow = m.highRow;
        lowCol = m.lowCol;
        highCol = m.highCol;
        p = m.p;
        m.p = nullptr;
    }

    Matrix<T> &operator=(const Matrix<T> &a)
    {
        if (this == &a)
        {
            return *this;
        }
        delete p;
        int size = a.highRow - a.lowRow + 1;
        p = new Matrix<T>(a.lowRow, a.highRow, a.lowCol, a.highCol);
        for (int i = 0; i < size; i++)
            (*p)[i] = a.p[i];
        return *this;
    }

    SA<T> &operator[](int i)
    {
        if (i < lowRow || i > highRow)
        {

            cout << "index " << i << " out of range" << endl;
            exit(1);
        }
        return (*p)[i - lowRow];
    }

    friend ostream &operator<<(ostream &os, Matrix<T> s)
    {
        int size = s.highRow - s.lowRow + 1;
        cout << endl;
        for (int i = 0; i < size; i++)
            cout << s.p->operator[](i) << endl;
        return os;
    }

    // ~Matrix()
    // {
    //     cout << "MAtrix destructor" << endl;
    //     delete p;
    // }
};

Matrix<int> Multiply(Matrix<int> &first, Matrix<int> &m)
{

    if ((first.highCol - first.lowCol) != (m.highRow - m.lowRow))
    {
        cout << "Matrix Multiplication only possible when number of cols of first matrix equals number of rows of the m matrix." << endl;
        exit(0);
    }

    Matrix<int> ans(first.highRow - first.lowRow + 1, m.highCol - m.lowCol + 1);
    for (int i = 0; i < first.highRow - first.lowRow + 1; i++)
    {
        for (int j = 0; j < m.highCol - m.lowCol + 1; j++)
        {
            ans[i][j] = 0;
            for (int k = 0; k < first.highCol - first.lowCol + 1; k++)
            {
                ans[i][j] += first[i][k] * m[k][j];
            }
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
    cout << Multiply(m, n);
    return 0;
}