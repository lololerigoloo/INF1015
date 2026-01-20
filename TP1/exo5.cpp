/*
    INF1015 - Programmation I
    TP1 - Exercices 1 à 5
    Auteur: Laurent Corbeil et Tristan Gagné
    Date: 2026-01-20
    Description: Bonjour ce code est le numéro 5 le but est de lire un fichier 
    contenant des informations sur des étudiants et de compter le nombre d'étudiants 
    dans différents domaines d'étude en fonction d'une plage de matricules donnée.
*/

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct Etudiant
{
    int matricule;
    string sigle;
};

void RemplirEtudiant(Etudiant etudiant[], ifstream &fichier, int &nbrelem)
{
    while (fichier >> etudiant[nbrelem].matricule >> etudiant[nbrelem].sigle)
    {
        nbrelem++;
    }
    fichier.close();
}
void CompterDomaine(Etudiant etudiant[], int nbrelem, int min, int max, const string domaine[], int compteur[])
{
    for (int i = 0; i < nbrelem; i++)
    {
        if (etudiant[i].matricule >= min && etudiant[i].matricule <= max)
        {
            for (int j = 0; j < 5; j++)
            {
                if (etudiant[i].sigle[0] == domaine[j][0])
                {
                    compteur[j]++;
                    break;
                }
                else if (j == 4)
                {
                    compteur[4]++;
                }
            }
        }
    }
}
void AfficherResultat(int compteurDomaine[], const string domaine[])
{
    for (int j = 0; j < 5; j++)
    {
        if (j == 3)
        {
            cout << "Biomedicale      " << compteurDomaine[j] << endl;
            continue;
        }
        cout << domaine[j] << "      " << compteurDomaine[j] << endl;
    }
}

int main()
{
    const string domaine[] = {"Electrique", "Informatique", "Logiciel", "GBM", "Autre"};
    ifstream fichier("INF1015-TD1-H26-Fichiers/etudiants.txt");
    if (fichier.fail())
    {
        cout << "Erreur lors de l'ouverture du fichier." << endl;
        return 1;
    }
    Etudiant etudiants[400];
    int nbrelem = 0;
    RemplirEtudiant(etudiants, fichier, nbrelem);
    while (true)
    {
        int min = 0;
        int max = 0;
        cout << "Entrer la plage de matricules (0 0 pour terminer): ";
        cin >> min >> max;
        if (min == 0 && max == 0)
        {
            break;
        }
        if (min > max)
        {
            cout << "Plage invalide. Le minimum doit être inférieur ou égal au maximum." << endl;
            continue;
        }
        cout << "Dans cette plage, il y a ces nombres d'etudiants dans chaque domaine: " << endl;
        int compteurDomaine[5] = {0};
        CompterDomaine(etudiants, nbrelem, min, max, domaine, compteurDomaine);
        AfficherResultat(compteurDomaine, domaine);
    }
    return 0;
}