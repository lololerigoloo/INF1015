#pragma once
#include <memory>
#include <iostream>
#include "Jeu.hpp"
#include "Liste.hpp"
#include "Concepteur.hpp"

std::shared_ptr<Concepteur> lireConcepteur(Liste<Jeu>& lj, std::istream& f);
std::shared_ptr<Jeu> lireJeu(std::istream& f, Liste<Jeu>& lj);
Liste<Jeu> creerListeJeux(const std::string& nomFichier);
std::shared_ptr<Concepteur> chercherConcepteur(const Liste<Jeu>& listeJeux, const std::string& nom);
