#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

struct Head
{
    long length;
    struct Head *next;
};

static Head pool = {0, 0};

static Head *h = (Head *)new char[1000];

typedef char *Char_p;

const long WORDSIZE = sizeof(void *);



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

    void *operator new(size_t nbytes)
    {
        cout << "Operator new called. " << endl;
        if (pool.next)
        {
            Head *prev = &pool;
            for (Head *cur = &pool; cur; cur = cur->next)
            {
                if (cur->length >= nbytes)
                {
                    prev->next = cur->next;
                    return (void *)(Char_p(cur) + sizeof(Head));
                }
                else
                {
                    prev = cur;
                }
            }
        }

        h = (Head *)(((long)((Char_p(h) + WORDSIZE - 1)) / WORDSIZE) * WORDSIZE);
        h->next = 0;
        h->length = nbytes;
        h = (Head *)(Char_p(h) + nbytes + sizeof(Head));
        return (void *)(Char_p(h) - nbytes);
    }

    void operator delete(void *ptr)
    {
        cout << "Operator delete called." << endl;
        Head *p = (Head *)(Char_p(ptr) - sizeof(Head));
        p->next = pool.next;
        pool.next = p;
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
    SA<int> *z = new SA<int>(3, 2);
    SA<int> a(10), b(3, 5);
    b[3] = 3;
    b[4] = 4;
    b[5] = 5;
    int i;
    for (i = 0; i < 10; i++)
        a[i] = 10 - i;
    cout << "printing a the first time" << endl;
    cout << a << endl;
    cout << "printing using []" << endl;
    for (i = 0; i < 10; i++)
        cout << a[i] << endl;
    // write your own sort
    // Sort(a, 10);
    cout << "printing a the second time" << endl;
    cout << a << endl;
    b[4] = 12;
    cout << "printing b " << endl;
    cout << b << endl;
    a[10] = 12; // should print an error message and exit
    return 0;
}