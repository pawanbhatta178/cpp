#include <iostream>
using namespace std;

int countOnes(int n)
{
    int count = 0;
    while (n != 0)
    {
        n = n & (n - 1);
        count++;
    }
    return count;
}

int totalOnes(int n)
{
    int total = 0;
    for (int i = 0; i < n; i++)
    {
        total = total + countOnes(i);
    }
    return total;
}

int main()
{
    int n;
    std::cin >> n;
    std::cout << totalOnes(n) << endl;
}
