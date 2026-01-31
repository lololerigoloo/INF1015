#include <iostream>
#include <string>
#include <fstream>
using namespace std;
void f(int* p)
{
    *p = 6;
    p = new int(7);
}
void g(int*& r)
{
    *r = 9;
    r = new int(10);
}
int main()
{
    int* x;
    x = new int(3);
    cout << "La valeur de x est: " << *x << endl;
    int* y = x;
    cout << "La valeur de y est: " << *y << endl;
    *y = 4;
    cout << "Après modification, la valeur de x est: " << *x << endl;
    cout << "Après modification, la valeur de y est: " << *y << endl;
    int* z = new int(*x);
    *x = 5;
    cout << "Après modification, la valeur de x est: " << *x << endl;
    cout << "La valeur de z est: " << *z << endl;
    f(x);
    cout << "Après appel de f, la valeur de x est: " << *x << endl;
    cout << "Après appel de f, la valeur pointée par y est: " << *y << endl;
    int a = 6;
    g(x);
    cout << "Après appel de g, la valeur de x est: " << *x << endl;
    cout << "Après appel de g, la valeur pointée par y est: " << *y << endl;
    int* ptra = &a;
    g(ptra);
    f(&a);

    
}