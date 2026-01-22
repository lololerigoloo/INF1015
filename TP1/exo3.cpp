/*
    INF1015 - Programmation I
    TP1 - Exercices 1 à 5
    Auteur: Laurent Corbeil et Tristan Gagné
    Date: 2026-01-20
    Description: Bonjour ce code est le numéro 3 le but est de lire un fichier texte 
    et d'en afficher la valeur maximum et minimum
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
double max(double valeurs[], int nbrelem)
{
    for (int i = 1; i < nbrelem; i++)
    {
        if (valeurs[i] > valeurs[0])
        {
            valeurs[0] = valeurs[i];
        }
    }
    return valeurs[0];
}
double min(double valeurs[], int nbrelem)
{
    for (int i = 1; i < nbrelem; i++)
    {
        if (valeurs[i] < valeurs[0])
        {
            valeurs[0] = valeurs[i];
        }
    }
    return valeurs[0];
}
int nombreElements(ifstream &fichier)
{
    string ligne;
    int compteur = 0;
    while (getline(fichier, ligne))
    {
        compteur++;
    }
    cout << "Nombre d'éléments: " << compteur << endl;
    return compteur;
}
void transformerEnTableau(ifstream &fichier, double valeurs[])
{
    int compteur = 0;
    string nom;
    int valeur;
    while(fichier >> nom >> valeur)
    {
        valeurs[compteur] = valeur;
        compteur++;
    }
}

int main()
{
    ifstream fichier("INF1015-TD1-H26-Fichiers/aliments.txt");
    if (!fichier)
    {
        cout << "Erreur lors de l'ouverture du fichier." << endl;
        return 1;
    }
    else
    {
        cout << "Fichier ouvert avec succès." << endl;
        int nbrelem = nombreElements(fichier);
        fichier.clear();                 // Réinitialiser les indicateurs d'état du flux
        fichier.seekg(0, ios::beg);      // Revenir au début du fichier
        double valeurs[nbrelem];
        transformerEnTableau(fichier, valeurs);
        for (int i = 0; i < nbrelem; i++)
        {
            
            valeurs[i] = valeurs[i];
        }
        
        double maximum = max(valeurs, nbrelem);
        double minimum = min(valeurs, nbrelem);
        cout << "La valeur maximum est: " << maximum << endl;
        cout << "La valeur minimum est: " << minimum << endl;
    }
}