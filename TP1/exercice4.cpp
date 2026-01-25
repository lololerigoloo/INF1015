/*
    INF1015 - Programmation I
    TP1 - Exercices 1 à 5
    Auteur: Laurent Corbeil et Tristan Gagné
    Date: 2026-01-20
    Description: Bonjour ce code est le numéro 4 le but 
    de trouver un nombre n de place libre dans un tableau 2d   

*/
#include <iostream>
#include <random>

using namespace std;
const int rangees = 20;
const int placesParRangee = 10;

void initialiserTableau(int tableau[rangees][placesParRangee])
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);

    for (int i = 0; i < rangees; i++)
    {
        for (int j = 0; j < placesParRangee; j++)
        {
            tableau[i][j] = dis(gen);
        }
    }
}

void afficherTableau(int tableau[rangees][placesParRangee])
{
    for (int i = 0; i < rangees; i++)
    {
        for (int j = 0; j < placesParRangee; j++)
        {
            cout << tableau[i][j];
        }
        cout << endl;
    }
}
bool estDemandeValide(int n)
{
    return n >= 1 && n <= placesParRangee ;
}
void afficherPossibiliter(int tableau[rangees][placesParRangee], int nbplace)
{
    
   /* important les sieges sont numérotés comme suit : 1 2 3 4 5 6 7 8 9 10 rangée 1
                                                       1 2 3 4 5 6 7 8 9 10 rangée 2 
                                                       ...
                                                       ...
                                                       */
    int compteur = 0;
    for(int i = 0; i<rangees;i++)
    {
        for(int j = 0; j< placesParRangee; j++)
        {
            if(tableau[i][j] == 0)
            {
                
                compteur++; 
                if(compteur == nbplace)
                {
                    cout << "rangee " << i+1 << " sieges " << j - nbplace + 2 << " à " << j +1 << endl;
                    compteur--;
                }
            
            }
            else
            {
                compteur = 0;
            }
        }
        compteur = 0;
    }
}
int main()
{
    int cinema[rangees][placesParRangee];
    initialiserTableau(cinema);
    while(true)
    {
        int n;
        cout << "Entrez le nombre de places libres à trouver (entre 1 et " << placesParRangee << "): ";
        cin >> n;

        if (estDemandeValide(int(n)))
        {
            afficherTableau(cinema);
            cout << "Recherche de " << n << " places libres..." << endl;
            afficherPossibiliter(cinema, n);
            break; 
        }
        else
        {
            cout << "Demande invalide. Veuillez entrer un nombre entre 1 et " << placesParRangee << "." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    
    return 0;
}