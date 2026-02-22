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
    Liste(const Liste &autre);
    Liste &operator=(const Liste &autre);

    // Accès
    T &operator[](unsigned index);
    const T &operator[](unsigned index) const;
    // Ajout
    void ajouter(const T &element);
    void ajouter(const std::shared_ptr<T> &element);

    // Infos
    unsigned size() const { return nElements_; }
    int taille() const { return nElements_; }
    int capacite() const { return capacite_; }
    std::shared_ptr<T> getShared(int i) const { return elements_[i]; }

    // Recherche
    std::shared_ptr<T> trouver(const std::function<bool(const T &)> &critere) const;

private:
    void modifierCapacite();

    unsigned nElements_;
    unsigned capacite_;
    std::unique_ptr<std::shared_ptr<T>[]> elements_;
};

template <class T>
Liste<T>::Liste()
{
    nElements_ = 0;
    capacite_ = 2;
    elements_ = std::make_unique<std::shared_ptr<T>[]>(capacite_);
}
template <class T>
Liste<T>::Liste(const Liste &autre)
{
    nElements_ = autre.nElements_;
    capacite_ = autre.capacite_;
    elements_ = std::make_unique<std::shared_ptr<T>[]>(capacite_);

    for (unsigned i = 0; i < nElements_; i++)
        elements_[i] = autre.elements_[i];
}

template <class T>
void Liste<T>::ajouter(const T &element)
{
    if (nElements_ == capacite_)
        modifierCapacite();

    elements_[nElements_] = std::make_shared<T>(element);
    nElements_++;
}

template <class T>
void Liste<T>::ajouter(const std::shared_ptr<T> &element)
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

    auto nouveau = std::make_unique<std::shared_ptr<T>[]>(capacite_);

    for (unsigned i = 0; i < nElements_; i++)
        nouveau[i] = elements_[i];

    elements_ = std::move(nouveau);
}

template <class T>
T &Liste<T>::operator[](unsigned index)
{
    if (index >= nElements_)
        throw std::out_of_range("Index hors limites");

    return *elements_[index];
}

template <class T>
const T &Liste<T>::operator[](unsigned index) const
{
    if (index >= nElements_)
        throw std::out_of_range("Index hors limites");

    return *elements_[index];
}

template <class T>
std::shared_ptr<T> Liste<T>::trouver(const std::function<bool(const T &)> &critere) const
{
    for (unsigned i = 0; i < nElements_; i++)
    {
        if (critere(*elements_[i]))
            return elements_[i];
    }
    return nullptr;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const Liste<T> &liste)
{
    os << "Liste de " << liste.size() << " elements:\n";

    for (unsigned i = 0; i < liste.size(); i++)
    {
        os << "  [" << i << "] " << *liste.getShared(i) << "\n";
    }

    return os;
}
template <class T>
Liste<T>& Liste<T>::operator=(const Liste<T>& autre)
{
    if (this == &autre)
        return *this;

    nElements_ = autre.nElements_;
    capacite_ = autre.capacite_;

    elements_ = std::make_unique<std::shared_ptr<T>[]>(capacite_);

    for (unsigned i = 0; i < nElements_; i++)
        elements_[i] = autre.elements_[i];

    return *this;
}
