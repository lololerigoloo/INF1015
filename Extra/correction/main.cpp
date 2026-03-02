#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Etudiant
{
    unsigned matricule;
    double cote;
    string nomComplet;
};
Etudiant trouverPlusProcheCote(const vector<Etudiant>& tableau, double coteProcheDe) {
    Etudiant etudiantPlusProcheCote = tableau[0];
    double diffmin = abs(etudiantPlusProcheCote.cote - coteProcheDe);
    for (int i= 1; i < tableau.size(); i++){
        double diffactuel = abs(tableau[i].cote - coteProcheDe);
        if(diffactuel < diffmin){
            etudiantPlusProcheCote = tableau[i];
            diffmin = diffactuel;
        }
        
    }
    return etudiantPlusProcheCote;
    // TODO: Compléter la fonction
}
int main()
{
    vector<Etudiant> etudiants = {
        {12345, 85.5, "Alice Smith"},
        {67890, 92.0, "Bob Johnson"},
        {54321, 78.0, "Charlie Brown"},
        {98765, 88.5, "Diana Prince"}};

    double coteProcheDe = 90.0;
    Etudiant etudiantProche = trouverPlusProcheCote(etudiants, coteProcheDe);

    cout << "L'étudiant avec la cote la plus proche de " << coteProcheDe << " est : " << endl;
    cout << "Matricule: " << etudiantProche.matricule << endl;
    cout << "Cote: " << etudiantProche.cote << endl;
    cout << "Nom Complet: " << etudiantProche.nomComplet << endl;

    return 0;
}