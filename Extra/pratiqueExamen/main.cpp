#include "noeud.hpp"
#include "division.hpp"
#include <string>
#include <iostream>
using namespace std;
int main()
{
    string mike = "mike";
    Noeud bra = Noeud(mike);
    Noeud na = Noeud(mike , &bra,&bra); 
    na.setApres(&na);
    cout << na ;
    Division a{10,4};
    Division b{10,4};
    cout << a;
    cout << b;
    cout << (a+b) ;
    return 0;
}