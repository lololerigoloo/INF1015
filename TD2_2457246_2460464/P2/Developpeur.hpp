#pragma once
#include <string>
#include <utility>
#include "ListeJeux.hpp"

class Developpeur
{
public:
	Developpeur(const std::pair<std::string, ListeJeux> &paireNomJeux);
	~Developpeur();

	std::string Nom() const;
	unsigned nombreParticipationJeuxDansListe(const ListeJeux &liste);
	void mettreAJourListeJeux(const ListeJeux &nouvelleListe);
	void afficherInfosJeux();

private:
	// TODO: En faire une classe qui suit les principes OO.
	// TODO: La destruction d'un Developpeur doit s'assurer que la désallocation de ListeJeux est faite.
	// TODO: Les méthodes à faire...
	std::pair<std::string, ListeJeux> paireNomJeux_;
};
