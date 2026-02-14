// Fonctions pour lire le fichier binaire.
#include "lectureFichierJeux.hpp"
#include <fstream>
#include <cstdint>
#include "cppitertools/range.hpp"
#include "Liste.hpp"
#include "Jeu.hpp"
#include <memory>
#include "Concepteur.hpp"
using namespace std;

using UInt8 = uint8_t;
using UInt16 = uint16_t;

#pragma region "Fonctions de lecture de base"
// TODO: Remplacer lireUint8 et lireUint16 par une seule fonction générique qui permet les deux, mais permettre uniquement des types qui sont is_trivially_copyable_v (un trait de type).
template <typename T>
T lireEntier(istream &fichier)
{
	static_assert(is_trivially_copyable_v<T>, "Le type doit être trivially copyable.");
	T valeur = 0;
	fichier.read(reinterpret_cast<char *>(&valeur), sizeof(valeur));
	return valeur;
}
UInt8 lireUint8(istream &fichier)
{
	return lireEntier<UInt8>(fichier);
}

UInt16 lireUint16(istream &fichier)
{
	return lireEntier<UInt16>(fichier);
}

string lireString(istream &fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read(reinterpret_cast<char *>(&texte[0]), streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
#pragma endregion

const Concepteur *chercherConcepteur(const Liste<Jeu> &listeJeux, const string &nom)
{
	for (int i = 0; i < listeJeux.taille(); i++)
	{
		const Jeu &jeu = listeJeux[i];
		const Liste<Concepteur> &concepteurs = jeu.getConcepteurs();

		for (int j = 0; j < concepteurs.taille(); j++)
		{
			const Concepteur &c = concepteurs[j];

			if (c.getNom() == nom)
				return &c;
		}
	}
	return nullptr;
}

Concepteur *lireConcepteur(Liste<Jeu> &lj, istream &f)
{
	string nom = lireString(f);
	unsigned anneeNaissance = lireUint16(f);
	string pays = lireString(f);

	if(const_cast<Concepteur *>(chercherConcepteur(lj, nom)) == nullptr)
	{
		Concepteur concepteur = Concepteur();
		concepteur.setNom(nom);
		concepteur.setAnneeNaissance(anneeNaissance);
		concepteur.setPays(pays);
		return new Concepteur(concepteur);
	}
	else
	{
		return const_cast<Concepteur *>(chercherConcepteur(lj, nom));
	}
}

Jeu *lireJeu(istream &f, Liste<Jeu> &lj)
{
	string titre = lireString(f);
	unsigned anneeSortie = lireUint16(f);
	string developpeur = lireString(f);
	unsigned nConcepteurs = lireUint8(f);
	// TODO: Compléter la fonction (équivalent de lireJeu du TD2).
	Liste<Concepteur> listeConcepteurs = Liste<Concepteur>();
	for (unsigned int i = 0; i < nConcepteurs; i++)
	{
		Concepteur *concepteur = lireConcepteur(lj, f);
		listeConcepteurs.ajouter(*concepteur);
	}
	Jeu jeu = Jeu();
	jeu.setTitre(titre);
	jeu.setAnneeSortie(anneeSortie);
	jeu.setDeveloppeur(developpeur);
	jeu.setConcepteurs(listeConcepteurs);
	return new Jeu(jeu);
}

Liste<Jeu> creerListeJeux(const string &nomFichier)
{
	ifstream f(nomFichier, ios::binary);
	f.exceptions(ios::failbit);
	int nElements = lireUint16(f);
	// TODO: Compléter la fonction.
	Liste<Jeu> listeJeux = Liste<Jeu>();
	for ([[maybe_unused]] int i : iter::range(nElements))
	{
		Jeu *jeu = lireJeu(f, listeJeux);
		listeJeux.ajouter(*jeu);
	}

	return listeJeux;
}
