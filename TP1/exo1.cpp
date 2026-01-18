// Bonjour ce code est le numéro 1 le but est de faire un trinagle isocèle d'étoiles
#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Entrez la hauteur du triangle isocèle: ";
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        // Afficher les espaces
        for (int j = i; j < n; ++j) {
            cout << " ";
        }
        // Afficher les étoiles
        for (int k = 1; k <= (2 * i - 1); ++k) {
            cout << "*";
        }
        cout << endl;
    }

    return 0;
}