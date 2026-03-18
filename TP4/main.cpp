#include <fstream>
#include "bibliotheque_cours.hpp"
#include <cstdint>
#include <iostream>
#include "Affichable.hpp"
#include "Personnage.hpp"
#include "Heros.hpp"
#include "Vilain.hpp"
#include "VilainHeros.hpp"
#include <vector>

using namespace std;

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
	fichier.read(reinterpret_cast<char *>(&texte[0]), texte.size());
	return texte;
}

static const string trait =
	"═════════════════════════════════════════════════════════════════════════";
template <typename T>
void afficherListe(const vector<T*> &liste)
{
	static_assert(std::derived_from<T, Affichable>, "T doit dériver de Affichable");
	for (auto p : liste)
	{
		cout << *p;
		cout << trait << endl;
	}
}

int main()
{
	bibliotheque_cours::activerCouleursAnsi();

	ifstream fichierHeros("heros.bin", ios::binary);
	ifstream fichierVilains("vilains.bin", ios::binary);

	fichierHeros.exceptions(ios::failbit);
	fichierVilains.exceptions(ios::failbit);

	vector<Hero *> heros;
	vector<Vilain *> vilains;
	vector<Personnage *> personnages;

	UInt16 nbVilains = lireUint16(fichierVilains);

	for (UInt16 i = 0; i < nbVilains; i++)
	{
		string nom = lireString(fichierVilains);
		string parution = lireString(fichierVilains);
		string objectif = lireString(fichierVilains);

		Vilain *v = new Vilain(nom, parution, objectif);

		vilains.push_back(v);
		personnages.push_back(v);
	}

	UInt16 nbHeros = lireUint16(fichierHeros);
	for (UInt16 i = 0; i < nbHeros; i++)
	{
		string nom = lireString(fichierHeros);
		string parution = lireString(fichierHeros);
		string nomEnnemi = lireString(fichierHeros);
		UInt8 nbAllies = lireUint8(fichierHeros);

		vector<string> nomsAllies;
		for (UInt8 j = 0; j < nbAllies; j++)
			nomsAllies.push_back(lireString(fichierHeros));


		Vilain *ennemiPtr = nullptr;
		for (auto v : vilains)
		{
			if (v->getNom() == nomEnnemi)
			{
				ennemiPtr = v;
				break;
			}
		}
		Hero *h = new Hero(nom, parution, nomsAllies, ennemiPtr);
		heros.push_back(h);
		personnages.push_back(h);
	}

	for (auto h : heros)
		h->changerCouleur(94);

	for (auto v : vilains)
		v->changerCouleur(91);



	afficherListe(heros);
	afficherListe(vilains);
	afficherListe(personnages);

	VilainHero *vh = new VilainHero(
		*vilains[0],
		*heros[0]);

	vh->changerCouleur(95);

	vh->afficher(cout);
	cout << trait << endl;

	personnages.push_back(vh);

	for (auto p : personnages)
	{
		p->afficher(cout);
		cout << trait << endl;
	}

	// =====================
	// Delete mémoire
	// =====================

	for (auto p : personnages)
		delete p;

	return 0;
}