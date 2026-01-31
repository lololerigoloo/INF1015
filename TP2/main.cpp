#include "Jeu.hpp"
#include <iostream>
#include <fstream>
#include <span>
#include "cppitertools/range.hpp"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp" // Ajout des numéros de ligne des "new" dans le rapport de fuites.  Doit être après les include du système, qui peuvent utiliser des "placement new" (non supporté par notre ajout de numéros de lignes).
#include <cstdint>

using namespace std;
using namespace iter;

#pragma region "Fonctions de base pour vous aider"
typedef uint8_t UInt8;
typedef uint16_t UInt16;
UInt8 lireUint8(istream &fichier)
{
	UInt8 valeur = 0;
	fichier.read((char *)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(istream &fichier)
{
	UInt16 valeur = 0;
	fichier.read((char *)&valeur, sizeof(valeur));
	return valeur;
}
string lireString(istream &fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char *)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
#pragma endregion

// faite TODO: Fonction qui cherche un designer par son nom dans une ListeJeux.  Devrait utiliser span.
Designer *trouverDesignerParNom(const span<const Jeu *const> &panJeux, const Designer &nomRecherche)
{
	/*
	Parcours tous les jeux dans la liste de jeux.
	Pour chaque jeu, parcourt tous les designers associés.
	Si le nom du designer correspond au nom recherché, retourne un pointeur vers ce designer.
	Si aucun designer avec le nom recherché n'est trouvé, retourne nullptr.
	*/
	string nomRechercheStr = nomRecherche.nom;
	for (const Jeu *jeu : panJeux)
	{
		for (unsigned i = 0; i < jeu->designers.nElements; ++i)
		{
			Designer *designer = jeu->designers.elements[i];
			if (designer->nom == nomRechercheStr)
			{
				return designer;
			}
		}
	}

	return nullptr;
}

Designer *lireDesigner(istream &fichier)
{
	Designer designer = {};
	designer.nom = lireString(fichier);
	designer.anneeNaissance = lireUint16(fichier);
	designer.pays = lireString(fichier);

	// Faite TODO: Ajouter en mémoire le designer lu. Il faut revoyer le pointeur créé.
	// TIP: Afficher un message lorsque l'allocation du designer est réussie pour aider au débogage.
	// Vous pouvez enlever l'affichage une fois que le tout fonctionne.
	Designer *nouveauDesigner = new Designer(designer);

	// Faite TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	return nouveauDesigner; // TODO: Retourner le pointeur vers le designer crée.
}

// faite TODO: Fonction qui change la taille du tableau de jeux de ListeJeux.
void agrandirListeJeux(ListeJeux &liste)
{
	unsigned nouvelleCapacite = (liste.capacite == 0) ? 2 : liste.capacite * 2;
	Jeu **nouveauxElements = new Jeu *[nouvelleCapacite];

	// Copier les anciens éléments dans le nouveau tableau
	if (liste.nElements > 0)
	{
		for (unsigned i = 0; i < liste.nElements; ++i)
		{
			nouveauxElements[i] = liste.elements[i];
		}
	}

	// Libérer l'ancien tableau
	for (unsigned i = 0; i < liste.nElements; ++i)
	{
		liste.elements[i] = nullptr;
	}

	// Libérer l'ancien tableau
	delete[] liste.elements;

	// Mettre à jour la liste avec le nouveau tableau et la nouvelle capacité
	liste.elements = nouveauxElements;
	liste.capacite = nouvelleCapacite;
}
// faite TODO: Fonction pour ajouter un Jeu à ListeJeux.
void ajouterJeuAListeJeux(ListeJeux &liste, Jeu *jeuAAjouter)
{
	// Regarder si on doit agrandir la capacité
	if (liste.nElements >= liste.capacite)
	{
		agrandirListeJeux(liste);
	}
	// Ajouter le jeu à la liste
	liste.elements[liste.nElements] = jeuAAjouter;
	liste.nElements++;
}
// faite TODO: Fonction qui enlève un jeu de ListeJeux.
void enleverJeuDeListeJeux(ListeJeux &liste, Jeu *jeuAEnlever)
{
	// Trouver l'index du jeu à enlever
	unsigned indexAEnlever = liste.nElements; // Initialiser à une valeur invalide
	for (unsigned i = 0; i < liste.nElements; ++i)
	{
		if (liste.elements[i] == jeuAEnlever)
		{
			indexAEnlever = i;
			break;
		}
	}

	// Si le jeu n'a pas été trouvé, retourner
	if (indexAEnlever == liste.nElements)
	{
		return;
	}

	// Décaler les éléments après l'index à enlever
	for (unsigned i = indexAEnlever; i < liste.nElements - 1; ++i)
	{
		liste.elements[i] = liste.elements[i + 1];
	}

	liste.nElements--;
}

Jeu *lireJeu(istream &fichier)
{
	Jeu jeu = {};
	jeu.titre = lireString(fichier);
	jeu.anneeSortie = lireUint16(fichier);
	jeu.developpeur = lireString(fichier);
	jeu.designers.nElements = lireUint8(fichier);

	// faite TODO: Ajouter en mémoire le jeu lu. Il faut revoyer le pointeur créé.
	// TIP: Afficher un message lorsque l'allocation du jeu est réussie pour aider au débogage.
	// Vous pouvez enlever l'affichage une fois que le tout fonctionne.
	Jeu *nouveauJeu = new Jeu(jeu);
	nouveauJeu->designers.elements = new Designer *[nouveauJeu->designers.nElements];
	nouveauJeu->designers.capacite = nouveauJeu->designers.nElements;
	nouveauJeu->designers.nElements = 0;

	for ([[maybe_unused]] int i : iter::range(jeu.designers.nElements))
	{
		Designer *designer = lireDesigner(fichier);

		nouveauJeu->designers.elements[nouveauJeu->designers.nElements] = designer; // faite TODO: Ajouter le designer à la liste des designers du jeu.
		nouveauJeu->designers.nElements++;
		// faite TODO: Ajouter le jeu à la liste des jeux auquel a participé le designer.
		if (designer->listeJeuxParticipes.nElements >= designer->listeJeuxParticipes.capacite)
		{
			agrandirListeJeux(designer->listeJeuxParticipes);
		}
		ajouterJeuAListeJeux(designer->listeJeuxParticipes, nouveauJeu);
	}
	return nouveauJeu; // faite TODO: Retourner le pointeur vers le nouveau jeu.
}

ListeJeux creerListeJeux(const string &nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	int nElements = lireUint16(fichier);
	ListeJeux listeJeux = {};
	for ([[maybe_unused]] int n : iter::range(nElements))
	{

		Jeu *jeu = lireJeu(fichier); // faite TODO: Ajouter le jeu à la ListeJeux.
		// TIP: Afficher un message lorsque l'ajout du jeu à la liste est fait pour aider au débogage.
		ajouterJeuAListeJeux(listeJeux, jeu);
	}

	return listeJeux; // faite TODO: Renvoyer la ListeJeux.
}

// faite TODO: Fonction pour détruire un jeu (libération de mémoire allouée).
void detruireJeu(Jeu *jeu)
{
	// Détruire tous les designers associés au jeu
	for (unsigned i = 0; i < jeu->designers.nElements; ++i)
	{
		Designer *designer = jeu->designers.elements[i];
		// Enlever ce jeu de la liste des jeux du designer
		enleverJeuDeListeJeux(designer->listeJeuxParticipes, jeu);
		// Si le designer n'a plus de jeux, le détruire
		if (designer->listeJeuxParticipes.nElements == 0)
		{
			delete designer;
			// TIP: Afficher un message lorsque le designer est détruit pour aider au débogage.
		}
	}
	// Détruire le tableau des designers
	delete[] jeu->designers.elements;
	// Détruire le jeu lui-même
	delete jeu;
	// TIP: Afficher un message lorsque le jeu est détruit pour aider au débogage.
}

// faite TODO: Fonction pour détruire une ListeJeux et tous ses jeux.
void detruireListeJeux(ListeJeux &liste)
{
	for (unsigned i = 0; i < liste.nElements; ++i)
	{
		detruireJeu(liste.elements[i]);
	}
	delete[] liste.elements;
	liste.nElements = 0;
	liste.capacite = 0;
	liste.elements = nullptr;
}
// faite TODO: Fonction pour afficher les infos d'un designer.
void afficherDesigner(const Designer &designer)
{
	cout << "Nom: " << designer.nom << endl;
	cout << "Année de naissance: " << designer.anneeNaissance << endl;
	cout << "Pays: " << designer.pays << endl;
	cout << "Nombre de jeux participés: " << designer.listeJeuxParticipes.nElements << endl;
	for (unsigned i = 0; i < designer.listeJeuxParticipes.nElements; ++i)
	{
		Jeu *jeu = designer.listeJeuxParticipes.elements[i];
		cout << "  - " << jeu->titre << " (" << jeu->anneeSortie << ")" << endl;
	}
}

// faite TODO: Fonction pour afficher les infos d'un jeu ainsi que ses designers.

void afficherJeu(const Jeu &jeu)
{
	cout << "Titre: " << jeu.titre << endl;
	cout << "Année de sortie: " << jeu.anneeSortie << endl;
	cout << "Développeur: " << jeu.developpeur << endl;
	cout << "Designers:" << endl;
	for (unsigned i = 0; i < jeu.designers.nElements; ++i)
	{
		Designer *designer = jeu.designers.elements[i];
		cout << "  - " << designer->nom << " (" << designer->pays << ", né en " << designer->anneeNaissance << ")" << endl;
	}
}

// faite TODO: Fonction pour afficher tous les jeux de ListeJeux, séparés par un ligne.
//  Votre ligne de séparation doit être différent de celle utilisée dans le main.
void afficherListeJeux(const ListeJeux &liste)
{
	for (unsigned i = 0; i < liste.nElements; ++i)
	{
		afficherJeu(*liste.elements[i]);
		static const string rainbowSep =
			"\033[31m──────────────── "
			"\033[33mW\033[32ma\033[36mz\033[34ma\033[35ma\033[31ma\033[33ma\033[32ma\033[36ma "
			"\033[34m────────────────\033[0m\n";

		cout << rainbowSep;

		// cout << "\n\033[34m-------------------(.)(.)---------------------\033[0m\n"
	}
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
#pragma endregion

	int *fuite = new int; // Pour vérifier que la détection de fuites fonctionne; un message devrait dire qu'il y a une fuite à cette ligne.

	ListeJeux listeJeux = creerListeJeux("jeux.bin"); // faite TODO: Appeler correctement votre fonction de création de la liste de jeux.

	static const string ligneSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	cout << ligneSeparation << endl;
	cout << "Premier jeu de la liste :" << endl;
	afficherJeu(*listeJeux.elements[0]); // faite TODO: Afficher le premier jeu de la liste (en utilisant la fonction).  Devrait être Chrono Trigger.

	cout << ligneSeparation << endl;

	afficherListeJeux(listeJeux); // faite TODO: Appel à votre fonction d'affichage de votre liste de jeux.
	// faite TODO: Faire les appels à toutes vos fonctions/méthodes pour voir qu'elles fonctionnent et avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.

	// faite TODO: Détruire tout avant de terminer le programme.  Devrait afficher "Aucune fuite detectee." a la sortie du programme; il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.
	detruireListeJeux(listeJeux);
	delete fuite;
}
