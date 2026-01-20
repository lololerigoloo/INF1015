/* 
    INF1015 - Programmation I
    TP1 - Exercices 1 à 5
    Auteur: Laurent Corbeil et Tristan Gagné
    Date: 2026-01-20
    Description :Bonjour ce code est le numéro 2 le but est de faire un chiffrement de César 
    en ne modifiant que les lettres de l'alphabet et en remplaçant les autres caractères par '&' */
#include <iostream>
#include <string>
using namespace std;
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

int main()
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