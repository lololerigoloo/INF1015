#include <iostream>
template <typename T>
class Noeud{
    public:
    Noeud(const T& valeur, Noeud* avant = nullptr, Noeud* apres = nullptr) :
    _avant(avant),_apres(apres),_valeur(valeur){}
    template <typename U>
    friend std::ostream& operator<<(std::ostream& cout , const Noeud<U>& noeud);
    void setAvant(Noeud* noeud){ _avant = noeud;}
    void setApres(Noeud* noeud){ _apres = noeud;}

    private:
    Noeud* _avant;
    Noeud* _apres;
    T _valeur;
};
template <typename U>
std::ostream& operator<<(std::ostream& cout , const Noeud<U>& noeud)
{
    cout << "valeur : "<<noeud._valeur << std::endl;
    cout << "poointeur avant : " << noeud._avant << std::endl;
    cout << "poointeur apres : " << noeud._apres << std::endl;
    return cout;
}