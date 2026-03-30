#include "Personnage.hpp"
#include "Heros.hpp"
#include "Vilain.hpp"
#include "VilainHeros.hpp"
#include "ListeLiee.hpp"
#include <fstream>
#include <vector>
#include <functional>
#include <map>
#include "cppitertools/range.hpp"
#include "bibliotheque_cours.hpp"
using namespace std;
using namespace iter;

using UInt8 = uint8_t;
using UInt16 = uint16_t;

UInt8 lireUint8(istream &fichier)
{
	UInt8 valeur = 0;
	fichier.read(reinterpret_cast<char *>(&valeur), sizeof(valeur));
	return valeur;
}

UInt16 lireUint16(istream &fichier)
{
	UInt16 valeur = 0;
	fichier.read(reinterpret_cast<char *>(&valeur), sizeof(valeur));
	return valeur;
}

string lireString(istream &fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read(reinterpret_cast<char *>(&texte[0]), streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}

template <typename T>
vector<T> lireFichier(istream &fichier)
{
	vector<T> elements;
	for ([[maybe_unused]] int i : range(lireUint16(fichier)))
		elements.push_back(T(fichier));
	return elements;
}

ifstream ouvrirLectureFichierBinaire(const string &nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	return fichier;
}

// Permet d'avoir une référence non-const à un objet temporaire.
template <typename T>
T &temporaireModifiable(T &&objet) { return objet; }

template <typename T>
vector<T> lireFichier(const string &nomFichier)
{
	return lireFichier<T>(temporaireModifiable(
		ouvrirLectureFichierBinaire(nomFichier)));
}

template <typename T>
Iterateur<T> trouverParNom(ListeLiee<T> &liste, const string &nom)
{
	Iterateur<T> fin = liste.end();
	for (Iterateur<T> pos = liste.begin(); pos != fin; pos.avancer())
	{
		if ((*pos).getNom() == nom)
			return pos;
	}
	return fin;
}

int main()
{
#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
#pragma endregion

	// Trait de separation
	static const string trait =
		"═════════════════════════════════════════════════════════════════════════";

	static const string separateurSections = "\033[95m" + trait + "\033[0m\n";
	static const string separateurElements = "\033[33m" + trait + "\033[0m\n";

	//{ Solutionnaire du TD4:
	vector<Heros> heros = lireFichier<Heros>("heros.bin");
	vector<Vilain> vilains = lireFichier<Vilain>("vilains.bin");
	vector<unique_ptr<Personnage>> peronnages; // Doit être des pointeurs pour le polymorphisme, l'énoncé ne force pas les unique_ptr.

#if 1 // TODO: Vous n'avez pas à conserver ces affichages pour le TD5, ils sont pour le solutionnaire du TD4:
	cout << separateurSections << "Heros:" << endl;
	for (auto &h : heros)
	{
		cout << separateurElements;
		h.changerCouleur(cout, 0);
		h.afficher(cout);
	}

	cout << separateurSections << "Vilains:" << endl;
	for (auto &v : vilains)
	{
		cout << separateurElements;
		v.changerCouleur(cout, 0);
		v.afficher(cout);
	}

	for (auto &h : heros)
		peronnages.push_back(make_unique<Heros>(h));

	for (auto &v : vilains)
		peronnages.push_back(make_unique<Vilain>(v));

	peronnages.push_back(make_unique<VilainHeros>(vilains[1], heros[2]));

	cout << separateurSections << "Personnages:" << endl;
	for (auto &p : peronnages)
	{
		cout << separateurElements;
		p->changerCouleur(cout, 0);
		p->afficher(cout);
	}
	cout << separateurSections << "Un autre vilain heros (exemple de l'énoncé du TD):" << endl;
	VilainHeros kefkaCrono(vilains[2], heros[0]);
	kefkaCrono.changerCouleur(cout, 1);
	kefkaCrono.afficher(cout);
#endif
	//}

	// TODO: Transférez les héros du vecteur heros dans une ListeLiee.
	cout << separateurSections << "Liste liée de héros:" << endl;
	cout << "\033[0m"; // Réinitialise la couleur, pour que les couleurs différentes des héros soient plus visibles dans la liste liée."
	ListeLiee<Heros> listeHeros;
	for (const auto &h : heros)
	{
		listeHeros.push_back(h);
	}

	// TODO: Créez un itérateur sur la liste liée à la position du héros Alucard
	//  Servez-vous de la fonction trouverParNom définie plus haut
	Iterateur<Heros> iterateurAlucard = trouverParNom(listeHeros, "Alucard");

	// TODO: Servez-vous de l'itérateur créé précédemment pour trouver l'héroine Aya Brea,
	//  en sachant qu'elle se trouve plus loin dans la liste.
	Iterateur<Heros> iterateurAyaBrea = iterateurAlucard;
	while (iterateurAyaBrea != listeHeros.end() && (*iterateurAyaBrea).getNom() != "Aya Brea")
	{
		iterateurAyaBrea.avancer();
	}

	// TODO: Ajouter un hero bidon à la liste avant Aya Brea en vous servant de l'itérateur.
	listeHeros.insert(iterateurAyaBrea, Heros("HeroBidon", "JeuBidon", "EnnemiBidon"));

	// TODO: Assurez-vous que la taille de la liste est correcte après l'ajout.
	cout << ((listeHeros.size() == (heros.size() + 1)) ? "Taille de la liste après ajout correcte" : "Taille de la liste après ajout incorrect");
	cout << " (" << listeHeros.size() << " ," << heros.size() << ")" << endl;

	// TODO: Reculez votre itérateur jusqu'au héros Mario et effacez-le en utilisant l'itérateur, puis affichez le héros suivant dans la liste (devrait êter "Naked Snake/John").
	Iterateur<Heros> iterateurMario = iterateurAlucard;
	while (iterateurMario != listeHeros.end() && (*iterateurMario).getNom() != "Mario")
	{
		iterateurMario.reculer();
	}
	iterateurMario = listeHeros.erase(iterateurMario);
	cout << "Héros suivant après effacement de Mario: " << (*iterateurMario).getNom() << endl;

	// TODO: Assurez-vous que la taille de la liste est correcte après le retrait.
	cout << "Taille de la liste après retrait de Mario: " << (listeHeros.size() == heros.size()) << " (" << listeHeros.size() << " ," << heros.size() << ")" << endl;

	// TODO: Effacez le premier élément de la liste.
	listeHeros.erase(listeHeros.begin());

	// TODO: Affichez votre liste de héros en utilisant un itérateur. La liste débute
	//  avec le héros Randi et n'a pas Mario.
	//  Servez-vous des methodes begin et end de la liste...
	cout << separateurSections << "Héros dans la liste liée après modifications:" << endl;
	cout << "\033[0m"; // Réinitialise la couleur, pour que les couleurs différentes des héros soient plus visibles dans la liste liée."
	for (Iterateur<Heros> it = listeHeros.begin(); it != listeHeros.end(); it++)
	{
		it->afficher(cout);
		cout << trait << endl;
	}

	// TODO: Refaite le même affichage mais en utilisant une simple boucle "for" sur intervalle.
	for (const auto &hero : listeHeros)
	{
		hero.afficher(cout);
		cout << trait << endl;
	}

	// TODO: Utilisez un conteneur pour avoir les héros en ordre alphabétique (voir point 2 de l'énoncé).
	map<string, Heros> herosParNom;
	for (const auto &hero : listeHeros)
	{
		herosParNom[hero.getNom()] = hero;
	}

	cout << separateurSections << "Héros en ordre alphabétique:" << endl;
	// Réinitialise la couleur, pour que les couleurs différentes des héros soient plus visibles dans la liste liée."
	cout << "\033[0m";
	for (const auto &[nom, hero] : herosParNom)
	{
		hero.afficher(cout);
		cout << "\n";
	}
	// TODO: Assurez-vous de n'avoir aucune ligne non couverte dans les classes pour la liste liée.  Il peut y avoir des lignes non couvertes dans les personnages

	// Explication de la complexiter
	//                            |||||||||||||||||
	//                            |||||||||||||||||
	//                            |||||||||||||||||
	//                            |||||||||||||||||
	//                            |||||||||||||||||
	//                            |||||||||||||||||
	//                            |||||||||||||||||
	//                            |||||||||||||||||
	//                            |||||||||||||||||
	//                            |||||||||||||||||
	//                            |||||||||||||||||
	//                            |||||||||||||||||
	//                       |||||||||||||||||||||||||||
	// 					      |||||||||||||||||||||||||
	//                         |||||||||||||||||||||||
	//                          |||||||||||||||||||||
	//                           |||||||||||||||||||
	//                            |||||||||||||||||
	//                             |||||||||||||||
	//                              |||||||||||||
	//                               |||||||||||
	//                                |||||||||
	//                                 |||||||
	//                                  |||||
	//                                   |||
	//                                    |
	//                          c'etait long a dessiner
	// ici on va afficher un heros par son nom ceci ce fait en O(log n) grâce à la map, alors que dans la liste liée c'était O(n).
	// la raison est binary search tree (BST) qui est la structure de données utilisée pour implémenter la map, alors que la liste
	// liée nécessite de parcourir tous les éléments jusqu'à trouver celui qu'on cherche ce qui est O(n). la raison de O(log n) pour 
	// la map est que dans un BST équilibré, à chaque étape de la recherche, on peut éliminer la moitié des éléments restants, ce qui 
	// conduit à une complexité logarithmique.
	if (auto&& it = herosParNom.find("Randi"); it != herosParNom.end())
	{
		cout << separateurSections << "Affichage de Randi à partir de la map:" << endl;
		it->second.afficher(cout);
	}
	else
	{
		cout << "Randi n'a pas été trouvé dans la map." << endl;
	}
}
