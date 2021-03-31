#include <iostream>
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
};

class Polynomial
{
private:
    Term *head;

public:
    Polynomial()
    {
        this->head = NULL;
    }
    Polynomial(int coef, int pow)
    {
        Term *current = head;
        if (coef == 0)
        {
            return;
        }
        Term t(coef, pow, NULL);
        if (current == NULL)
        {
            current = &t;
        }
        else
        {
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = &t;
        }
    }
};