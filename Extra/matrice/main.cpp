#include "Matrice.hpp"
#include <iostream>
#include "joueur.hpp"
using namespace std;

int main()
{
    Matrice<int> m(3, 4);
    m(1, 2) = 42;
    std::cout << m(1, 2) << std::endl;
    std::cout << m << std::endl;
    Matrice<Joueur> joueurs(2, 2);
    joueurs(0, 0) = Joueur("Alice");
    joueurs(0, 1) = Joueur("Bob");
    joueurs(1, 0) = Joueur("Charlie");
    joueurs(1, 1) = Joueur("Diana");
    joueurs.Aggrandir(3, 3);
    cout << joueurs << endl;
    return 0;
}