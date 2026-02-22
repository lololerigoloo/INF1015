#include <iostream>
#include <fstream>
#include "Liste.hpp"
#include "Concepteur.hpp"
#include "Jeu.hpp"
#include "lectureFichierJeux.hpp"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
using namespace std;

// TODO: Vos surcharges d'opérateur <<

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
#pragma endregion

	Liste<Jeu> listeJeux = creerListeJeux("jeux.bin");
	static const string ligneSeparation = "\n\033[92m"
										  "══════════════════════════════════════════════════════════════════════════"
										  "\033[0m\n";

	cout << ligneSeparation;
	for (int i = 0; i < listeJeux.taille(); i++)
	{
		cout << "\033[93mJeu #" << i + 1 << ":\033[0m\n";
		const Jeu &jeu = listeJeux[i];
		cout << jeu << endl;
	}
	cout << ligneSeparation;
	cout << "\033[93 Test numero 3 des critere \033[0m " << endl;
	cout << "\033[93mNombre total de jeux:\033[0m " << listeJeux.size() << endl;
	cout << "\033[93mCapacité de la liste:\033[0m " << listeJeux.capacite() << endl;
	cout << ligneSeparation;
	cout << "\033[93mTest numero 4 des critere jeux a l'indice 2 et concepteur a l'indice 1:\033[0m" << endl;
	cout << "\033[93mJeu trouvé:\033[0m " << listeJeux[2].getTitre() << endl;
	cout << "\033[93mConcepteur trouvé:\033[0m: " << listeJeux[2].getConcepteurs()[1].getNom() << endl;
	cout << ligneSeparation;
	cout << "\033[93mTest numero 5 des critere trouver un jeu avec lambda:\033[0m" << endl;
	auto c1 = listeJeux[0].trouverConcepteur(
		[](const Concepteur &c)
		{
			return c.getNom() == "Yoshinori Kitase";
		});

	auto c2 = listeJeux[1].trouverConcepteur(
		[](const Concepteur &c)
		{
			return c.getNom() == "Yoshinori Kitase";
		});

	cout << "Adresse 1: " << c1.get() << endl;
	cout << "Adresse 2: " << c2.get() << endl;

	if (c1 == c2)
		cout << "\033[93mLes deux pointeurs sont identiques\033[0m" << endl;

	cout << "Annee: " << c1->getAnneeNaissance() << endl;
	cout << ligneSeparation;
	cout << "\033[93mTest numero 6 des critere  afficher la liste de jeux avec operator <<\033[0m" << endl;
	cout << listeJeux << endl;
	cout << ligneSeparation;
	cout << "\033[93mTest numero 7 des critere Tester la copie\033[0m" << endl;
	Jeu copieJeu = listeJeux[2];
	auto concepteurJeu0 =
		listeJeux[0].getConcepteurs().getShared(0);
	auto nouvelleListe = copieJeu.getConcepteurs();
	nouvelleListe.ajouter(concepteurJeu0);
	copieJeu.setConcepteurs(nouvelleListe);
	cout << "\033[93mJeu original:\033[0m\n"
		 << listeJeux[2] << endl;
	cout << "\033[93mJeu copié modifié:\033[0m\n"
		 << copieJeu << endl;
	auto ptrOriginal =
		listeJeux[2].getConcepteurs().getShared(0);
	auto ptrCopie =
		copieJeu.getConcepteurs().getShared(0);
	cout << "Adresse concepteur original: "
		 << ptrOriginal.get() << endl;
	cout << "Adresse concepteur copie:    "
		 << ptrCopie.get() << endl;
	if (ptrOriginal == ptrCopie)
		cout << "\033[93mLes deux pointeurs sont identiques\033[0m" << endl;
	else
		cout << "\033[93mLes deux pointeurs sont différents\033[0m" << endl;

	listeJeux = Liste<Jeu>();

	// TODO: L'affichage de listeJeux et l'écriture dans le fichier devraient fonctionner.

	// TODO: Compléter le main avec les tests demandés.
	// TODO: S'assurer qu'aucune ligne de code est non couverte.
	// NOTE: Il n'est pas nécessaire de couvrir les getters/setters simples fournis; il faut tester si vous en ajoutez ou les modifiez.
	// NOTE: Pour Liste, qui est générique, on demande de couvrir uniquement pour Liste<Jeu>, pas pour tous les types.
}