#include <iostream>
using namespace std;

char one()
{
    cout << "one\n";
    return '1';
}

char two()
{
    cout << "two\n";
    return '2';
}

int main(int, char **)
{
    // 1:
    cout << one()
         << '\n'
         << two()
         << '\n';

    // 2:
    operator<<(
        operator<<(
            operator<<(
                operator<<(
                    cout,
                    one()),
                '\n'),
            two()),
        '\n');
}