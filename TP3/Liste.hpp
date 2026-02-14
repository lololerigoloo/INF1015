#pragma once
#include <memory>
#include <functional>
#include <stdexcept>

template <class T>
class Liste
{
public:
    // Constructeur
    Liste();

    // Accès
    T& operator[](unsigned index);
    const T& operator[](unsigned index) const;

    // Ajout
    void ajouter(const T& element);
    void ajouter(const std::shared_ptr<T>& element);

    // Infos
    unsigned size() const { return nElements_; }
    int taille() const { return nElements_; }

    // Recherche
    T& trouver(const std::function<bool(const T&)>& critere);

private:
    void modifierCapacite();

    unsigned nElements_;
    unsigned capacite_;
    std::shared_ptr<T>* elements_;
};


template <class T>
Liste<T>::Liste()
{
    nElements_ = 0;
    capacite_ = 2;
    elements_ = new std::shared_ptr<T>[capacite_];
}

template <class T>
void Liste<T>::ajouter(const T& element)
{
    if (nElements_ == capacite_)
        modifierCapacite();

    elements_[nElements_] = std::make_shared<T>(element);
    nElements_++;
}

template <class T>
void Liste<T>::ajouter(const std::shared_ptr<T>& element)
{
    if (nElements_ == capacite_)
        modifierCapacite();

    elements_[nElements_] = element;
    nElements_++;
}

template <class T>
void Liste<T>::modifierCapacite()
{
    capacite_ *= 2;
    std::shared_ptr<T>* nouveau = new std::shared_ptr<T>[capacite_];

    for (unsigned i = 0; i < nElements_; i++)
        nouveau[i] = elements_[i];

    delete[] elements_;
    elements_ = nouveau;
}

template <class T>
T& Liste<T>::operator[](unsigned index)
{
    if (index >= nElements_)
        throw std::out_of_range("Index hors limites");

    return *elements_[index];
}

template <class T>
const T& Liste<T>::operator[](unsigned index) const
{
    if (index >= nElements_)
        throw std::out_of_range("Index hors limites");

    return *elements_[index];
}

template <class T>
T& Liste<T>::trouver(const std::function<bool(const T&)>& critere)
{
    for (unsigned i = 0; i < nElements_; i++)
    {
        if (critere(*elements_[i]))
            return *elements_[i];
    }
    throw std::runtime_error("Element non trouve");
}
