#include <iostream>
#include <random>
using namespace std;

int main()
{
    const int SIZE = 10;
    int tableau[SIZE];
    int tabFutur[SIZE];

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 1);
    uniform_real_distribution<double> luck(0, 2);

    int essais = 0;

    while (true)
    {
        essais++;

        // Initialisation aleatoire
        for (int i = 0; i < SIZE; i++)
            tableau[i] = dist(gen);

        bool echec = false;

        for (int generation = 1; generation <= 1000; generation++)
        {
            for (int i = 0; i < SIZE; i += 2)
            {
                int number = tableau[i] + tableau[i + 1];
                double randomVal = luck(gen);

                if (number == 0 && randomVal <= 0.5)
                {
                    int choix = dist(gen);
                    tabFutur[i] = choix;
                    tabFutur[i + 1] = 1 - choix;
                }
                else if (number == 0 || (number == 2 && randomVal <= 0.25))
                {
                    tabFutur[i] = 0;
                    tabFutur[i + 1] = 0;
                }
                else
                {
                    int val = (randomVal <= number) ? 1 : 0;
                    tabFutur[i] = val;
                    tabFutur[i + 1] = val;
                }
            }

            int sum = 0;
            for (int i = 0; i < SIZE; i++)
            {
                tableau[i] = tabFutur[i];
                sum += tableau[i];
            }

            if (sum == 0 || sum == SIZE)
            {
                echec = true;
                break; // cette simulation est rejetee
            }
        }

        if (!echec)
        {
            cout << "SUCCES apres " << essais << " essais" << endl;
            cout << "etat final a 1000 generations :" << endl;
            for (int i = 0; i < SIZE; i++)
                cout << tableau[i] << " ";
            cout << endl;
            break;
        }
    }

    return 0;
}
