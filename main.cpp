#include <iostream>
#include <random>
#include <chrono>
#include <thread>
using namespace std;

int main() {
    cout << "wow on a reussi" << endl;
    cout << "VERSION TEST 123" << endl;

    const int SIZE = 10;
    int tableau[SIZE] = {};

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 1);
    uniform_real_distribution<double> luck(0, 2);

    // Initialisation du tableau
    for (int i = 0; i < SIZE; i++) {
        tableau[i] = dist(gen);
        cout << tableau[i] << " ";
    }
    cout << endl;

    int generation = 1;
    int tabFutur[SIZE] = {};
    int sum = 0;
    while (true) 
    {
        cout << "ceci est la " << generation << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        
        for (int i = 0; i < SIZE; i += 2) 
        {
            int number = tableau[i] + tableau[i + 1];
            double randomVal = luck(gen);

            if (number == 0 && randomVal <= 0.5f) 
            {
                int choix = dist(gen);
                if(choix == 1)
                {
                tabFutur[i] = 0;
                tabFutur[i + 1] = 1;
                }
                else
                {
                    tabFutur[i] = 1;
                tabFutur[i + 1] = 0;
                }
                
            } 
            else if (number ==0 ||(number == 2 && randomVal <= 0.25f))
            {
                tabFutur[i] = 0;
                tabFutur[i + 1] = 0; 
            }
            else 
            {
                if (randomVal <= number) 
                {
                    tabFutur[i] = 1;
                    tabFutur[i + 1] = 1;
                } 
                else 
                {
                    tabFutur[i] = 0;
                    tabFutur[i + 1] = 0;
                }
            }
        }

        // Copier tabFutur dans tableau
        for (int i = 0; i < SIZE; i++)
        {
            tableau[i] = tabFutur[i];
            sum += tabFutur[i];
        }
        // Affichage de la nouvelle génération
        for (int i = 0; i < SIZE; i++)
        {
            cout << tableau[i] << " ";
            
        }
        if (sum == 0)
        {
            cout << "la mutation est disparu" << endl;
            break;
        }
        else if (sum == SIZE)
        {
            cout << "la mutation a gagner" << endl;
            break;
        }
            
        sum = 0;
        
        cout << endl;   
        generation++;
    }

    return 0;
}
