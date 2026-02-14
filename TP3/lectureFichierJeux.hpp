// Fonctions pour lire le fichier binaire.
#pragma once
#include "Jeu.hpp"
#include "Liste.hpp"
#include "Concepteur.hpp"
#include <iostream>


Concepteur* lireConcepteur(Liste<Jeu>& lj, std::istream& f);
Jeu* lireJeu(std::istream& f, Liste<Jeu>& lj);
Liste<Jeu>creerListeJeux(const std::string& nomFichier);
const Concepteur* chercherConcepteur(const Liste<Jeu>& listeJeux, const std::string& nom);