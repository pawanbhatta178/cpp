#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

class Term
{
public:
    int coefficient, exponent;
    Term *next;
    Term()
    {
        next = NULL;
    }
    Term(int coef, int pow, Term *nextTerm)
    {
        coefficient = coef;
        exponent = pow;
        next = nextTerm;
    }

    ~Term()
    {
        //By overwriting default destructor
    }

    friend ostream &operator<<(ostream &os, Term t)
    {

        cout << t.coefficient << "x^" << t.exponent;
        return os;
    }

    friend ostream &operator<<(ostream &os, Term &t)
    {

        cout << t.coefficient << "x^" << t.exponent;
        return os;
    }
};

class Polynomial
{
private:
    Term *head;

public:
    Polynomial()
    {
        head = NULL;
    }

    void insertTerm(int coef, int pow)
    {

        if (coef == 0)
        {
            return;
        }

        Term t(coef, pow, NULL);

        if (head == NULL)
        {
            head = &t;
        }
        else
        {
            Term *current = head;
            while (current != NULL)
            {
                current = current->next;
            }
            current = &t;
        }
        // cout << t << endl;
    }

    void printPolynomial()
    {

        cout << head->exponent << endl;
        cout << head->next->exponent << endl;
        cout << head->next->next->exponent << endl;
    }

    // friend ostream &operator<<(ostream &os, Polynomial p)
    // {

    //     if (p.head != NULL)
    //     {

    //         Term *current = p.head;
    //         cout << current;
    //         while (current->next != NULL)
    //         {
    //             current = current->next;
    //             if (current->coefficient < 0)
    //             {
    //                 cout << "-" << current;
    //             }
    //             cout << "+" << current;
    //         }
    //     }
    //     return os;
    // }

    // ~Polynomial()
    // {
    //     Term *current = head;
    //     while (current != NULL)
    //     {
    //         Term *temp = current->next;
    //         delete current;
    //         current = temp;
    //     }
    // }
};

int main()
{
    Polynomial p;
    p.insertTerm(2, 3);
    p.insertTerm(9, 9);
    p.insertTerm(9, 4);
    p.printPolynomial();
}