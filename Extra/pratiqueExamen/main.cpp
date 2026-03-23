#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <span>
#include <functional>
using namespace std;
auto affichageGauche (int largeur , char remplissage = ' '){
    return [=](string s)
    {
        cout << s;
        for(int i = s.size(); i < largeur; i++)
        {
            cout << remplissage;
        }
        cout << endl;
    };
}


// template<typename T, typename Pred>
// vector<T> trouversi(vector<T>& v, Pred pred){
//     span<T> s(v);
//     vector<T> res;
//     for(const T& i : s){
//         if(pred(i)){
//             res.push_back(i);
//         }
//     }
//     return res;
// }
class Liste{
public:
    Liste();
    Liste(const Liste& autre);
    Liste& operator = (const Liste& autre);
    void aggrandire();
    void ajouter(int ajout);
    void modifier(int index, int valeur);
    friend ostream &operator<<(ostream &os, const Liste &liste);
    private:
    vector<unique_ptr<int>> element_;
    int capaciter_;
    int nbElems_;
};
Liste::Liste() : capaciter_(0), nbElems_(0) {}
Liste& Liste::operator = (const Liste& autre){
    if(this == &autre){
        return *this;
    }
    capaciter_ = autre.capaciter_;
    nbElems_ = autre.nbElems_;
    element_.resize(capaciter_);
    for(int i = 0; i < nbElems_; i++){
        element_[i] = make_unique<int>(*(autre.element_[i]));
    }
    return *this;
}
Liste::Liste(const Liste& autre){
    *this = autre;
}
class Etudiant{};
int main()
{

    // vector<int> v = {1, 2, 3, 4, 5};
    // vector<string> s = {"Hello", "World", "C++", "Programming"};
    // vector<int> resultat = trouversi(v, [] (int x) { return x % 2 == 0; });
    // vector<string> resultat2 = trouversi(s, [] (const string& str) { return str.size() > 5; });
    // cout << "Résultat : ";
    // for(int i : resultat){
    //     cout << i << " ";
    // }
    // cout << endl;
    // cout << "Résultat 2 : ";
    // for(const string& str : resultat2){
    //     cout << str << " ";
    // }
    // cout << endl;
    // // auto g = f(5);
    // cout << "Résultat de g : " << g << endl; // Affiche 8
    // cout << "Valeur de a après l'appel de f : " << a << endl; // Affiche 3
    auto colonene1 = affichageGauche(7, '*');
    auto colonene2 = affichageGauche(7, '-');
    auto colonene3 = affichageGauche(8, '=');
    colonene1("A");
    colonene2("B");
    colonene3("C");
    unique_ptr<shared_ptr<Etudiant[]>> p1 = make_unique<shared_ptr<Etudiant[]>>(5);
}

// using Role = string; // Déclare que Role est le même type que string.

// class Projet
// {
// public:
//     Projet(const string &nom, const string &echeance);
//     string getNom() const;

//     friend ostream &operator<<(ostream &os, const Projet &projet);

// private:
//     string nom_;
//     string echeance_;
// };

// class Employe
// {
// public:
//     Employe(const Role &role, const string &nom);

//     void ajouterProjet(shared_ptr<Projet> projet);
//     string getNom() const;

//     friend ostream &operator<<(ostream &os, const Employe &employe);

// private:
//     Role role_;
//     string nom_;
//     vector<shared_ptr<Projet>> projets_;
// };

// class Groupe
// {
// public:
//     static constexpr int nMaxEmployesParGroupe = 10;

//     Groupe(const string &nom);

//     Employe *trouverEmploye(const string &nomEmploye) const;
//     void ajouterEmploye(const Employe &employe);
//     void attribuerProjet(shared_ptr<Projet> projet, const string &nomEmploye);
//     Groupe operator = (const Groupe &autre){
//         nom_ = autre.nom_;
//         nEmployes_ = autre.nEmployes_;
//         for(int i = 0; i < nEmployes_; i++){
//             employes_[i] = make_unique<Employe>(*(autre.employes_[i]));
//         }
//         return *this;
//     }
//     friend ostream &operator<<(ostream &os, const Groupe &groupe);
//     friend class Tests;

// private:
//     string nom_;
//     int nEmployes_;
//     unique_ptr<Employe> employes_[nMaxEmployesParGroupe];
// };
// Employe *Groupe::trouverEmploye(const string &nomEmploye) const
// {
//     std::span<const std::unique_ptr<Employe>> s(employes_, nEmployes_);

//     for (const auto &emp : s)
//     {
//         if (emp && emp->getNom() == nomEmploye)
//         {
//             return emp.get();
//         }
//     }
//     return nullptr;
// }
// void Groupe::ajouterEmploye(const Employe& employe){
//     if(nEmployes_ >= nMaxEmployesParGroupe){
//         throw runtime_error("Nombre maximum d'employés atteint");
//     }
//     if(trouverEmploye(employe.getNom()) != nullptr){
//         throw runtime_error("Employé déjà présent dans le groupe");
//     }
//     employes_[nEmployes_] = make_unique<Employe>(employe);
//     nEmployes_++;
// }

// int main()
// {
// }
// // #include <iostream>
// // #include <vector>
// // #include <span>
// // using namespace std;

// // class GestionNotes {
// // public:
// //     GestionNotes(vector<int>& notes) : notes_(notes) {}

// //     //  Trouver si une note existe
// //     bool contient(int valeur);

// //     // 2 Trouver l'index d'une note (-1 si absent)
// //     int trouverIndex(int valeur);

// //     //  Calculer la moyenne
// //     double moyenne();

// //     // Compter combien de notes sont >= seuil
// //     int compterReussites(int seuil);

// // private:
// //     vector<int>& notes_;
// // };

// // bool GestionNotes::contient(int val){
// //     span<int> s(notes_);

// //     for (int note : s){
// //         if(note == val){
// //             return true;
// //         }
// //     }
// //     return false;
// // }
// // int GestionNotes::trouverIndex(int val){
// //     span<int> s(notes_);

// //     for (size_t i = 0; i < s.size(); i++){
// //         if(s[i] == val){
// //             return i;
// //         }
// //     }
// //     return -1;
// // }
// // double GestionNotes::moyenne(){
// //     span<int> s(notes_);
// //     if(s.empty()){
// //         return 0.0;
// //     }
// //     int somme = 0;
// //     for (int note : s){
// //         somme += note;
// //     }
// //     return static_cast<double>(somme) / s.size();
// // }
// // int GestionNotes::compterReussites(int seuil){
// //     span<int> s(notes_);
// //     int count = 0;
// //     for (int note : s){
// //         if(note >= seuil){
// //             count++;
// //         }
// //     }
// //     return count;
// // }
// // int main(){

// // }
// // // #include <iostream>
// // // #include <memory>
// // // #include <vector>
// // // #include <cmath>
// // // #include <functional>
// // // using namespace std;

// // // // template <typename T>
// // // // class Liste
// // // // {
// // // // public:
// // // //     Liste();
// // // //     Liste(const Liste& autre);
// // // //     void aggrandire();
// // // //     void ajouter(T ajout);
// // // //     void modifier(int index, T valeur);
// // // //     template <typename U>
// // // //     friend ostream &operator<<(ostream &os, const Liste<U> &liste);

// // // // private:
// // // //     vector<unique_ptr<T>> element_;
// // // //     int capaciter_;
// // // //     int nbElems_;
// // // // };

// // // // template <typename U>
// // // // void Liste<U>::modifier(int index, U valeur)
// // // // {
// // // //     if(index < (nbElems_-1) ){
// // // //         return;
// // // //     }
// // // //     element_[index] = move(make_unique<U>(valeur));
// // // // }

// // // // template <typename U>
// // // // Liste<U>::Liste(const Liste<U>& autre)
// // // //     : capaciter_(autre.capaciter_), nbElems_(autre.nbElems_)
// // // // {
// // // //     element_.resize(capaciter_);
// // // //     for(int i =0; i<nbElems_; i++){
// // // //         element_[i]= (make_unique<U>(*(autre.element_[i])));
// // // //     }
// // // // }
// // // // template <typename U>
// // // // Liste<U>::Liste() : capaciter_(0), nbElems_(0) {}
// // // // template <typename U>
// // // // void Liste<U>::aggrandire()
// // // // {
// // // //     capaciter_ = (capaciter_ <= 0) ? 1 : capaciter_ * 2;
// // // //     vector<unique_ptr<U>> nv(capaciter_);
// // // //     for (int i = 0; i < nbElems_; i++)
// // // //     {
// // // //         nv[i] = move(element_[i]);
// // // //     }
// // // //     element_ = move(nv);
// // // // }
// // // // template <typename U>
// // // // void Liste<U>::ajouter(U ajout)
// // // // {
// // // //     if (nbElems_ >= capaciter_)
// // // //         aggrandire();

// // // //     element_[nbElems_] = make_unique<U>(ajout);
// // // //     nbElems_++;
// // // // }
// // // // template <typename U>
// // // // ostream &operator<<(ostream &os, const Liste<U> &liste)
// // // // {
// // // //     for (int i = 0; i < liste.nbElems_; i++)
// // // //     {
// // // //         os << *(liste.element_[i]) << " ";
// // // //     }
// // // //     os << endl;
// // // //     return os;
// // // // }
// // // // int main()
// // // // {
// // // //     Liste<int> n;
// // // //     n.ajouter(1);
// // // //     n.ajouter(2);
// // // //     auto v = n ;
// // // //     cout << n;
// // // //     cout << v;
// // // //     n.modifier(1,10);
// // // //     cout << n;
// // // //     cout << v;
// // // // }

// // // function<double(double)> Sinus()
// // // {
// // //     return [](double x)
// // //     {
// // //         return sin(x);
// // //     };
// // // }
// // // function<double(double, double)> Add()
// // // {
// // //     return [](double x, double y)
// // //     {
// // //         return x + y;
// // //     };
// // // }
// // // function<double(double)> Carre()
// // // {
// // //     return [](double x)
// // //     {
// // //         return x * x;
// // //     };
// // // }
// // // function<double(double)> Mul(double x)
// // // {
// // //     return [=](int y)
// // //     { return y * x; };
// // // }
// // // function<double(double)> Affine(double a, double b)
// // // {
// // //     return [=] (int x){return x*a +b ;};
// // // }
// // // function<bool(double ,double)> Bigger(){
// // //     return [] (double a , double b) {return a>b;};
// // // }
// // // function <double(double)> compose(function<double(double)> f,function<double(double)>g){
// // //     return [=] (double x) { return f(g(x));};
// // // }
// // // int main()
// // // {

// // //     auto sinu = Sinus();
// // //     auto add = Add();

// // //     cout << sinu(2);
// // //     cout << endl;
// // //     cout << add(2, 2);
// // //     cout << endl;
// // //     cout << Carre()(2);
// // //     cout << endl;
// // //     auto mull = Mul(5);
// // //     auto combi = compose(sinu , mull);
// // //     cout << "Test double fusion : " << combi(5);
// // //     cout << mull(3);
// // //     cout << " " << mull(6) << endl;
// // //     auto afi = Affine(4 , 2);
// // //     cout << "Test affine 4x+2 : "<<afi(1) << " " << afi(2) ;
// // //     auto big = Bigger();
// // //     cout << big(4,3);
// // //     cout << big(3,4);

// // //     // int base = 4;

// // //     // auto f = [&] (int x)mutable {return base+x+x;};
// // //     // std::cout << f(1);
// // //     // base =10;
// // //     // std::cout << f(1);
// // // }