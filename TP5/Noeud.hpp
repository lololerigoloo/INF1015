#pragma once
#include <gsl/pointers>
template<typename T> class ListeLiee;
template<typename T> class Iterateur;

template<typename T>
class Noeud
{
	friend class ListeLiee<T>;
	friend class Iterateur<T>;
public:
	//TODO: Constructeur(s).
	Noeud(const T& donnee) : donnee_(donnee), suivant_(nullptr), precedent_(nullptr) {}
private:
	//TODO: Attributs d'un noeud.
	T donnee_;
	Noeud<T>* suivant_;
	Noeud<T>* precedent_;
	friend class ListeLiee<T>;
	friend class Iterateur<T>;
};
