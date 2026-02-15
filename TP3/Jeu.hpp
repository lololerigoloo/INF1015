#pragma once
#include <string>
#include "Liste.hpp"
#include "Concepteur.hpp"
#include <functional>
#include <memory>

class Jeu
{
public:
	// TODO: un constructeur par défaut et un constructeur paramétré.
	friend std::ostream &operator<<(std::ostream &os, const Jeu &jeu);
	Jeu() = default;
	Jeu(std::string titre, unsigned anneeSortie, std::string developpeur, const Liste<Concepteur> &concepteurs)
		: titre_(move(titre)), anneeSortie_(anneeSortie), developpeur_(move(developpeur)), listeConcepteurs_(concepteurs) {}
	~Jeu() = default;
	const std::string &getTitre() const { return titre_; }
	void setTitre(std::string titre) { titre_ = move(titre); }
	unsigned getAnneeSortie() const { return anneeSortie_; }
	void setAnneeSortie(unsigned annee) { anneeSortie_ = annee; }
	const std::string &getDeveloppeur() const { return developpeur_; }
	void setDeveloppeur(std::string developpeur) { developpeur_ = move(developpeur); }
	void setConcepteurs(const Liste<Concepteur> &concepteurs) { listeConcepteurs_ = concepteurs; }
	const Liste<Concepteur> &getConcepteurs() const { return listeConcepteurs_; }
	std::shared_ptr<Concepteur> trouverConcepteur(
		const std::function<bool(const Concepteur &)> &critere) const;
	


// TODO: Votre méthode pour trouver un concepteur selon un critère donné par une lambda, en utilisant la méthode de Liste.

private:
std::string titre_;
unsigned anneeSortie_;
std::string developpeur_;
Liste<Concepteur> listeConcepteurs_;
// TODO: Attribut de la liste des concepteurs du jeu
}
;
