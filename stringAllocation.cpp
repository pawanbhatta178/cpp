#include <iostream>
#include <string>
using namespace std;

void *operator new(size_t size)
{
    cout << "Allocating from heap " << size << " bytes \n";
    return malloc(size);
}

int main()
{
    string string1("I m in Stack");
    string string2("I m in allocated in Heap");
}