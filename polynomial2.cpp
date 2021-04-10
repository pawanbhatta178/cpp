#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

class Polynomial
{
private:
    map<int, int> poly;

public:
    void insertTerm(int coef, int exp)
    {
        if (coef == 0)
        {
            return;
        }
        if (poly[exp] == 0)
        {
            poly[exp] = coef;
        }
        else
        {
            poly[exp] = poly[exp] + coef;
        }
    }

    Polynomial operator+(const Polynomial &a)
    {
        Polynomial ans;

        for (const auto &x : poly)
        {
            ans.insertTerm(x.second, x.first);
        }
        for (const auto &x : a.poly)
        {
            ans.insertTerm(x.second, x.first);
        }
        return ans;
    }

    Polynomial operator-(const Polynomial &a)
    {
        Polynomial ans;

        for (const auto &x : poly)
        {
            ans.insertTerm(x.second, x.first);
        }
        for (const auto &x : a.poly)
        {
            ans.insertTerm((-1) * x.second, x.first);
        }
        return ans;
    }

    Polynomial operator*(const Polynomial &a)
    {
        Polynomial ans;

        for (const auto &x : poly)
        {
            for (const auto &y : a.poly)
            {
                ans.insertTerm(x.second * y.second, x.first + y.first);
            }
        }

        return ans;
    }

    void print(ofstream &outFile)
    {
        bool termIsZero = false;
        int count = 0;
        for (const auto &x : poly)
        {
            //Coefficient is Zero, we dont print anything
            if (x.second == 0)
            {
                termIsZero = true;
                continue;
            }

            if (x.second > 0 && count > 0)
            {
                outFile << "+";
            }
            if (x.second == 1)
            {
                //print nth
            }
            else if (x.second == -1)
            {
                outFile << "-";
            }
            else
            {
                outFile << x.second;
            }

            if (x.first == 0)
            {
            }
            else if (x.first == 1)
            {
                outFile << "x";
            }
            else
            {
                outFile << "x^" << x.first;
            }
            count++;
        }

        //If the polynomial evaluates to zero
        if (count <= 1 && termIsZero)
        {
            outFile << "0";
        }

        outFile << endl
                << endl;
    }
};

int main()
{
    string inputName = "input.txt";
    ifstream input;
    input.open(inputName);

    string outputName = "output.txt";
    ofstream output;
    output.open(outputName);

    if (input.is_open() && output.is_open())
    {

        Polynomial poly1, poly2, sum;
        int count = 0;
        for (string line; getline(input, line);)
        {
            count++;
            istringstream ss(line);
            int coef, exp;

            if (count == 1)
            { //1st polynomial
                while (ss >> coef && ss >> exp)
                {
                    poly1.insertTerm(coef, exp);
                }
            }
            if (count == 2)
            { //2nd polynomial
                while (ss >> coef && ss >> exp)
                {
                    poly2.insertTerm(coef, exp);
                }
            }
        }
        Polynomial p;
        output << "poly1 = ";
        poly1.print(output);
        output << "poly2 = ";
        poly2.print(output);

        p = poly1 + poly2;
        output << "poly1 + poly2 = ";
        p.print(output);

        p = poly1 - poly2;
        output << "poly1 - poly2 = ";
        p.print(output);

        p = poly1 * poly2;
        output << "poly1 * poly2 = ";
        p.print(output);
    }
    input.close();
    output.close();
    return 0;
}