#include <iostream>
#include <fstream>
#include <string>
#include <cstdarg>
#include <sstream>
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

    friend ostream &operator<<(ostream &os, Term t)
    {
        if (t.coefficient != 0)
        {
            if (t.exponent == 0)
            {
                cout << t.coefficient;
            }
            else if (t.coefficient == 1 && t.exponent == 1)
            {
                cout << "x";
            }
            else if (t.coefficient == -1 && t.exponent == 1)
            {
                cout << "-x";
            }
            else if (t.coefficient == 1)
            {
                cout << "x^" << t.exponent;
            }
            else if (t.coefficient == -1)
            {
                cout << "-x^" << t.exponent;
            }
            else if (t.exponent == 1)
            {
                cout << t.coefficient << "x";
            }

            else
            {
                cout << t.coefficient << "x^" << t.exponent;
            }
        }
        return os;
    }

    friend ostream &operator<<(ostream &os, Term *t)
    {
        if (t->coefficient != 0)
        {
            if (t->exponent == 0)
            {
                cout << t->coefficient;
            }
            else if (t->coefficient == 1 && t->exponent == 1)
            {
                cout << "x";
            }
            else if (t->coefficient == -1 && t->exponent == 1)
            {
                cout << "-x";
            }
            else if (t->coefficient == 1)
            {
                cout << "x^" << t->exponent;
            }
            else if (t->coefficient == -1)
            {
                cout << "-x^" << t->exponent;
            }
            else if (t->exponent == 1)
            {
                cout << t->coefficient << "x";
            }
            else
            {
                cout << t->coefficient << "x^" << t->exponent;
            }
        }
        return os;
    }
};

class Polynomial
{
private:
    Term *head, *tail;

public:
    Polynomial()
    {
        head = NULL;
        tail = NULL;
    }

    void insertTerm(int coef, int pow)
    {

        if (coef == 0)
        {
            return;
        }

        Term *t = new Term(coef, pow, NULL);

        if (head == NULL)
        {
            head = t;
            tail = t;
        }
        else
        {
            tail->next = t;
            tail = tail->next;
        }
    }

    void consolidate()
    {
        insertionSort(&head);
        Term *current = head;
        while (current != NULL)
        {
            if (current->next != NULL && current->exponent == current->next->exponent)
            {
                current->coefficient = current->coefficient + current->next->coefficient;
                Term *temp = current->next->next;
                current->next = temp;
                continue;
            }
            //updating tail
            if (current->next == NULL)
            {
                tail = current;
            }
            current = current->next;
        }
    }

    void insertionSort(Term **head_ref)
    {
        // Initialize sorted linked list
        Term *sorted = NULL;

        // Traverse the given linked list and insert every
        // node to sorted
        Term *current = *head_ref;
        while (current != NULL)
        {
            // Store next for next iteration
            Term *next = current->next;

            // insert current in sorted linked list
            sortedInsert(&sorted, current);

            // Update current
            current = next;
        }

        // Update head_ref to point to sorted linked list
        *head_ref = sorted;
    }

    void sortedInsert(Term **head_ref, Term *new_node)
    {
        Term *current;
        /* Special case for the head end */
        if (*head_ref == NULL || (*head_ref)->exponent <= new_node->exponent)
        {
            new_node->next = *head_ref;
            *head_ref = new_node;
        }
        else
        {
            /* Locate the node before the point of insertion */
            current = *head_ref;
            while (current->next != NULL &&
                   current->next->exponent > new_node->exponent)
            {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
        }
    }

    void printPolynomial()
    {
        Term *t = head;
        while (t != NULL)
        {
            if (t == head)
            {
                cout << t;
            }
            else
            {
                if (t->coefficient > 0)
                {
                    cout << "+";
                }
                cout << t;
            }
            t = t->next;
        }
        cout << endl;
    }

    Polynomial operator+(const Polynomial &a)
    {
        Polynomial ans;
        Term *t = head;
        while (t != NULL)
        {
            ans.insertTerm(t->coefficient, t->exponent);

            t = t->next;
        }
        Term *t2 = a.head;
        while (t2 != NULL)
        {
            ans.insertTerm(t2->coefficient, t2->exponent);

            t2 = t2->next;
        }
        ans.consolidate();
        return ans;
    }

    Polynomial operator-(const Polynomial &a)
    {
        Polynomial ans;
        Term *t = head;
        while (t != NULL)
        {
            ans.insertTerm(t->coefficient, t->exponent);
            t = t->next;
        }
        Term *t2 = a.head;
        while (t2 != NULL)
        {
            ans.insertTerm((-1) * t2->coefficient, t2->exponent);
            t2 = t2->next;
        }
        ans.consolidate();
        return ans;
    }

    Polynomial operator*(const Polynomial &a)
    {
        Polynomial ans;
        Term *t = head;
        while (t != NULL)
        {
            Term *t2 = a.head;
            while (t2 != NULL)
            {
                ans.insertTerm(t->coefficient * t2->coefficient, t->exponent + t2->exponent);
                t2 = t2->next;
            }
            t = t->next;
        }

        ans.consolidate();
        return ans;
    }

    friend ostream &operator<<(ostream &os, Polynomial p)
    {
        Term *t = p.head;

        if (t->coefficient == 0)
        {
            cout << "0";
        }

        while (t != NULL)
        {
            if (t == p.head)
            {
                cout << t;
            }
            else
            {
                if (t->coefficient > 0)
                {
                    cout << "+";
                }
                cout << t;
            }
            t = t->next;
        }
        cout << endl;
        return os;
    }

    friend ostream &operator<<(ostream &os, Polynomial *p)
    {
        Term *t = p->head;

        if (t->coefficient == 0)
        {
            cout << "0";
        }

        while (t != NULL)
        {
            if (t == p->head)
            {
                cout << t;
            }
            else
            {
                if (t->coefficient > 0)
                {
                    cout << "+";
                }
                cout << t;
            }
            t = t->next;
        }
        cout << endl;
        return os;
    }

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
    string inputName = "input.txt";
    ifstream input;
    input.open(inputName);

    if (input.is_open())
    {
        Polynomial first, second;
        int count = 0;
        for (string line; getline(input, line);)
        {
            count++;
            istringstream ss(line);
            int coef, exp;
            Polynomial p;

            while (ss >> coef && ss >> exp)
            {
                p.insertTerm(coef, exp);
            }
            if (count == 1)
            { //1st polynomial
                first = p;
            }
            if (count == 2)
            { //2nd polynomial
                second = p;
            }
        }
        cout << "As given in the file: " << endl;
        cout << first;
        cout << second;
        cout << "\nCononical Form:" << endl;
        first.consolidate();
        second.consolidate();
        cout << first;
        cout << second;
        cout << "\nPerforming Addition yields:" << endl;
        Polynomial p;
        p = first + second;
        cout << p;
        cout << "\nPerforming Subtraction yields:" << endl;
        p = first - second;
        cout << p;
        cout << "\nPerforming Multiplication yields:" << endl;
        p = first * second;
        cout << p;
    }
    else
    {
        cout << "ERROR: The input file with following name does not exists or there was problem reading it: " << inputName << endl;
    }
}