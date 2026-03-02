#include "Concepteur.hpp"
#include <utility>
#include <ostream>

std::ostream& operator<<(std::ostream& os, const Concepteur& c)
{
	os << "Concepteur: " << c.getNom() << ", Année de naissance: " << c.getAnneeNaissance() << ", Pays: " << c.getPays();
	return os;
}