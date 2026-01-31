#include <iostream>
#include <string>
using namespace std;
struct Address 
{
    unsigned numeroCivic;
    string rue, ville, codePostal;
};
int main()  
{
    Address adr = {1200 , "rue des lilas" , "Montreal" , "H1A2B3"};
    cout << adr.numeroCivic << " " << adr.rue << " " << adr.ville << " " << adr.codePostal << endl;
    
}