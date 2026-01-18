#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 1);

    const int NUMBER_OF_TESTS = 10000000;
    int successCount[12] = {}; // positions 0..11

    for (int test = 0; test < NUMBER_OF_TESTS; test++) {
        // Toutes les positions sont initialement non visitées sauf la position 11 (position 12)
        bool visited[12] = {false};
        visited[11] = true;

        int position = 11;       // Commence à la position 12
        int visitedCount = 1;    // Déjà visité la position 12

        while (visitedCount < 10) { // Arrête quand 10 positions sont visitées
            int direction = dist(gen) == 0 ? -1 : 1;
            position = (position + direction + 12) % 12; // modulo corrigé

            if (!visited[position]) {
                visited[position] = true;
                visitedCount++;
            }
        }

        // Compte les positions non visitées
        for (int i = 0; i < 12; i++) {
            if (!visited[i]) {
                successCount[i]++;
            }
        }

        if (test % 1000000 == 0) {
            cout << "Completed " << test / 1000000 << " million tests." << endl;
        }
    }

    // Affiche les probabilités
    for (int i = 0; i < 12; i++) {
        cout << "Position " << (i + 1) << " was the last unvisited in "
             << successCount[i] << " out of " << NUMBER_OF_TESTS
             << " tests. Probability: "
             << (static_cast<double>(successCount[i]) / NUMBER_OF_TESTS) * 100.0
             << "%" << endl;
    }
}
