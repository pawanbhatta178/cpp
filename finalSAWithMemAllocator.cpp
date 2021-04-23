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
        // cout << "SA default constructor called" << endl;
        lowRow = 0;
        highRow = -1;
        p = NULL;
    }

    SA(int l, int h)
    {
        // cout << "SA constructor with bounds called" << endl;
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
        // cout << "SA constructor without bounds called" << endl;
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
        // cout << "SA copy constructor called" << endl;
        int size = a.highRow - a.lowRow + 1;
        p = new T[size];
        for (int i = 0; i < size; i++)
            p[i] = a.p[i];
        lowRow = a.lowRow;
        highRow = a.highRow;
    }

    SA &operator=(const SA &a)
    {
        // cout << "SA Assignment operator called" << endl;
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
        return *this; //dereference of this will call copy constructor
    }

    SA &&operator=(SA &&a)
    {
        // cout << "SA move assign operator called" << endl;
        delete[] p;
        p = a.p;
        lowRow = a.lowRow;
        highRow = a.highRow;
        a.p = nullptr;
        return move(*this); //will not call copy constructor
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

    friend ostream &operator<<(ostream &os, SA &s)
    {
        // cout << "SA << operator called" << endl;
        int size = s.highRow - s.lowRow + 1;
        for (int i = 0; i < size; i++)
            cout << s.p[i] << " ";
        cout << endl;
        return os;
    }

    friend ostream &operator<<(ostream &os, SA &&s)
    {
        // cout << "SA << operator with rvalue param called" << endl;
        int size = s.highRow - s.lowRow + 1;
        for (int i = 0; i < size; i++)
            cout << s.p[i] << " ";
        cout << endl;
        return os;
    }

    friend ostream &operator<<(ostream &os, SA *s)
    {
        // cout << "SA << operator with rvalue param called" << endl;
        int size = s->highRow - s->lowRow + 1;
        for (int i = 0; i < size; i++)
            cout << s->p[i] << " ";
        cout << endl;
        return os;
    }

    void *operator new(size_t size)
    {
        // cout << "SA new operator called" << endl;
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
        // cout << "SA Delete Operator called" << endl;
        SA *s = (SA *)ptr;
        s->freepointer = newList;
        newList = s;
    }

    ~SA()
    {
        // cout << "SA Destructor called" << endl;
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
            cout << lr << " " << hr << " " << lc << " " << hc;
            cout << "Matrix constructor error in bounds definition" << endl;
            exit(1);
        }
        lowRow = lr;
        highRow = hr;
        lowCol = lc;
        highCol = hc;

        p = new SA<SA<T> >(lr, hr);
        for (int i = lr; i <= hr; i++)
        {
            (*p)[i] = SA<T>(lc, hc);
        }
    }

    Matrix(int rowCapacity, int colCapacity)
    {
        if (rowCapacity < 0 || colCapacity < 0)
        {
            cout << "Constructor error: Please instantiate Matrix of positive length" << endl;
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
        p = (SA<SA<T> > *)malloc(sizeof(SA<SA<T> >));
        memmove(p, a.p, sizeof(SA<SA<T> >));
        return *this;
    }

    Matrix<T> &&operator=(Matrix<T> &&a)
    {
        delete p;
        lowRow = a.lowRow;
        highRow = a.highRow;
        lowCol = a.lowCol;
        highCol = a.highCol;
        p = a.p;
        a.p = nullptr;
        return move(*this);
    }

    SA<T> &operator[](int i)
    {
        if (i < lowRow || i > highRow)
        {
            cout << "index " << i << " out of range in Matrix" << endl;
            exit(1);
        }
        return (*p)[i];
    }

    // Matrix<T> &operator*(const Matrix<T> &m)
    // {
    //     if ((highCol - lowCol) != (m.highRow - m.lowRow))
    //     {
    //         cout << "Matrix Multiplication only possible when number of cols of first matrix equals number of rows of the m matrix." << endl;
    //         exit(0);
    //     }

    //     Matrix<int> ans(highRow - lowRow + 1, m.highCol - m.lowCol + 1);

    //     for (int i = 0; i <= highRow - lowRow; i++)
    //     {
    //         for (int j = 0; j <= m.highCol - m.lowCol; j++)
    //         {
    //             ans[i][j] = 0;

    //             for (int k = 0; k <= highCol - lowCol; k++)
    //             {
    //                 ans[i][j] += (*this)[i + lowRow][k + lowCol] * m[k + m.lowRow][j + m.lowCol];
    //             }
    //         }
    //     }
    //     return ans;
    // }

    friend ostream &
    operator<<(ostream &os, Matrix<T> &s)
    {
        cout << endl;
        for (int i = s.lowRow; i <= s.highRow; i++)
            cout << s.p->operator[](i) << endl;
        return os;
    }

    ~Matrix()
    {
        delete p;
    }
};

Matrix<int> Multiply(Matrix<int> &first, Matrix<int> &m)
{

    if ((first.highCol - first.lowCol) != (m.highRow - m.lowRow))
    {
        cout << first.highCol << " " << first.lowCol << " " << m.highRow << " " << m.lowRow << endl;
        cout << "Matrix Multiplication only possible when number of cols of first matrix equals number of rows of the m matrix." << endl;
        exit(0);
    }

    Matrix<int> ans(first.highRow - first.lowRow + 1, m.highCol - m.lowCol + 1);

    for (int i = 0; i <= first.highRow - first.lowRow; i++)
    {
        for (int j = 0; j <= m.highCol - m.lowCol; j++)
        {
            ans[i][j] = 0;

            for (int k = 0; k <= first.highCol - first.lowCol; k++)
            {

                ans[i][j] += first[i + first.lowRow][k + first.lowCol] * m[k + m.lowRow][j + m.lowCol];
            }
        }
    }

    return ans;
}

int main()
{
    //specifying both upper and lower bounds for the first matrix
    int rowLow1 = 4;
    int colLow1 = 4;
    int rowHigh1 = 8;
    int colHigh1 = 8;

    //specifying only sizes for the 2nd matrix
    int rowHigh2 = 5;
    int colHigh2 = 8;

    // Initializing both first and second matrices
    Matrix<int> m(rowLow1, rowHigh1, colLow1, colHigh1);
    Matrix<int> n(rowHigh2, colHigh2);

    // Initializing random number generator.
    srand(time(0));

    //initializing 1st safe matrix
    for (int i = m.lowRow; i <= m.highRow; i++)
    {
        for (int j = m.lowCol; j <= m.highCol; j++)
        {
            m[i][j] = (rand() % 10);
        }
    }

    //initializing 2nd safe matrix
    for (int i = n.lowRow; i <= n.highRow; i++)
    {
        for (int j = n.lowCol; j <= n.highCol; j++)
        {
            n[i][j] = (rand() % 10);
        }
    }

    //Answer for matrix multiplication
    Matrix<int> ans(Multiply(m, n));

    cout << endl
         << "m =" << endl
         << m << endl;

    cout << "n =" << endl
         << n << endl;

    cout << "m * n =" << endl
         << ans;
}