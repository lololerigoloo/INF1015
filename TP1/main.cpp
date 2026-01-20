/*
    INF1015 - Programmation I
    TP1 - Exercices 1 à 5
    Auteur: Laurent Corbeil et Tristan Gagné
    Date: 2026-01-20
    Description: Programme principal qui exécute les exercices 1 à 5 pour le TP1 de inf1015 hiver 2026.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

using namespace std;


// Début de exo1.cpp
void exo1()
{
    int n;

    cout << "Entrez la hauteur du triangle isocèle: ";
    cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        // Afficher les espaces
        for (int j = i; j < n; ++j)
        {
            cout << " ";
        }
        // Afficher les étoiles
        for (int k = 1; k <= (2 * i - 1); ++k)
        {
            cout << "*";
        }
        cout << endl;
    }
}
// Fin de exo1.cpp

// Début de exo2.cpp
string caeserCipher(string phrase, int decalage)
{
    for (int i = 0; i < phrase.length(); i++)
    {
        if (isalpha(phrase[i]))
        {
            char caractere = islower(phrase[i]) ? phrase[i] : tolower(phrase[i]);
            phrase[i] = (caractere - 'a' + decalage) % 26 + 'a';
        }
        else
        {
            phrase[i] = '&'; // Ne pas modifier les caractères non alphabétiques
        }
    }
    return phrase;
}
bool isValidShift(int decalage)
{
    return decalage >= 1 && decalage <= 17; // regarder si le décalage est entre 1 et 17
}

int exo2()
{
    while (true)
    {
        int decalage;
        string phrase;

        cout << "Entrez le décalage (entre 1 et 17): ";
        cin >> decalage;
        cin.ignore(); // Ignorer le caractère de nouvelle ligne restant dans le flux d'entrée

        if (isValidShift(decalage))
        {
            cout << "Entrez la phrase à chiffrer: ";
            getline(cin, phrase);

            string phraseChiffree = caeserCipher(phrase, decalage);
            cout << "Phrase chiffrée: " << phraseChiffree << endl;
            break; // Sortir de la boucle après un chiffrement réussi
        }
        else
        {
// Debut Extra pris sur https://stackoverflow.com/questions/6486289/clear-console-screen-in-c
#ifdef _WIN32
            std::system("cls");
#else
            // Assume POSIX or other non-Windows
            std::system("clear");
#endif
            // Fin Extra pris sur https://stackoverflow.com/questions/6486289/clear-console-screen-in-c
            cout << "Décalage invalide. Veuillez entrer un nombre entre 1 et 17." << endl;
        }
    }
    return 0;
}

// Fin de exo2.cpp

// Debut de exo3.cpp
double Max(double valeurs[], int nbrelem)
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
double Min(double valeurs[], int nbrelem)
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
int NombreElements(ifstream &fichier)
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
vector<double> TransformerEnTableau(ifstream &fichier, int nbrelem)
{
    int compteur = 0;
    string nom;
    int valeur;
    vector<double> tableau(nbrelem);
    while (fichier >> nom >> valeur)
    {
        tableau[compteur] = valeur;
        compteur++;
    }
    return tableau;
}

void exo3()
{
    ifstream fichier("INF1015-TD1-H26-Fichiers/aliments.txt");
    if (!fichier)
    {
        cout << "Erreur lors de l'ouverture du fichier." << endl;
    }
    else
    {
        cout << "Fichier ouvert avec succès." << endl;
        int nbrelem = NombreElements(fichier);
        fichier.clear();            // Réinitialiser les indicateurs d'état du flux
        fichier.seekg(0, ios::beg); // Revenir au début du fichier
        vector<double> tableau = TransformerEnTableau(fichier, nbrelem);
        double valeurs[nbrelem];
        for (int i = 0; i < nbrelem; i++)
        {

            valeurs[i] = tableau[i];
        }
        double maximum = Max(valeurs, nbrelem);
        double minimum = Min(valeurs, nbrelem);
        cout << "La valeur maximum est: " << maximum << endl;
        cout << "La valeur minimum est: " << minimum << endl;
    }
}
// Fin de exo3.cpp

// Debut de exo4.cpp
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
    return n >= 1 && n <= placesParRangee;
}
void afficherPossibiliter(int tableau[rangees][placesParRangee], int nbplace)
{

    /* important les sieges sont numérotés comme suit : 1 2 3 4 5 6 7 8 9 10 rangée 1
                                                        1 2 3 4 5 6 7 8 9 10 rangée 2
                                                        ...
                                                        ...
                                                        */
    int compteur = 0;
    for (int i = 0; i < rangees; i++)
    {
        for (int j = 0; j < placesParRangee; j++)
        {
            if (tableau[i][j] == 0)
            {

                compteur++;
                if (compteur == nbplace)
                {
                    cout << "rangee " << i + 1 << " sieges " << j - nbplace + 2 << " à " << j + 1 << endl;
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
void exo4()
{
    int cinema[rangees][placesParRangee];
    initialiserTableau(cinema);
    while (true)
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
}

// Fin de exo4.cpp

// Debut de exo5.cpp
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

void exo5()
{
    const string domaine[] = {"Electrique", "Informatique", "Logiciel", "GBM", "Autre"};
    ifstream fichier("INF1015-TD1-H26-Fichiers/etudiants.txt");
    if (fichier.fail())
    {
        cout << "Erreur lors de l'ouverture du fichier." << endl;
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
}
// Fin de exo5.cpp

// Début de main.cpp
int main()
{
    cout << "Exercice 1:" << endl;
    exo1();
    cout << "\nExercice 2:" << endl;
    exo2();
    cout << "\nExercice 3:" << endl;
    exo3();
    cout << "\nExercice 4:" << endl;
    exo4();
    cout << "\nExercice 5:" << endl;
    exo5();
    cout << "\nTous les exercices sont terminés." << endl;
    return 0;
}
