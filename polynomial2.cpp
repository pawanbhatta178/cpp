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

    // void add(map<int, int> &poly1, map<int, int> &poly2, map<int, int> &sum)
    // {
    //     for (const auto &x : poly1)
    //     {
    //         if (poly2[x.first] != 0)
    //         {
    //             sum[x.first] = x.second + poly2[x.first];
    //             cout << "Added" << sum[x.first] << endl;
    //         }
    //         else
    //         {
    //             sum[x.first] = x.second;
    //         }
    //     }
    //     for (const auto &x : poly2)
    //     {
    //         if (poly1[x.first] == 0)
    //         {
    //             sum[x.first] = x.second;
    //         }
    //     }
    // }

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

    void print(ofstream &outFile)
    {
        int count = 0;
        for (const auto &x : poly)
        {
            //Coefficient is Zero, we dont print anything
            if (x.second == 0)
            {
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
        outFile << endl;
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
        Polynomial p = poly1 + poly2;
        poly1.print(output);
        poly2.print(output);
        p.print(output);
    }
    input.close();
    output.close();
    return 0;
}