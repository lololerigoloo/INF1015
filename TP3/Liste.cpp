// #include "Liste.hpp"
// using namespace std;

// template <typename T>
// Liste<T>::Liste()
// {
//     nElements_ = 0;
//     capacite_ = 2;
//     elements_ = new shared_ptr<T>[capacite_];
// }

// template <typename T>
// void Liste<T>::ajouter(const T& element)
// {
//     if (nElements_ == capacite_)
//         modifierCapacite();

//     elements_[nElements_] = make_shared<T>(element);
//     nElements_++;
// }

// template <typename T>
// void Liste<T>::ajouter(const std::shared_ptr<T>& element)
// {
//     if (nElements_ == capacite_)
//         modifierCapacite();

//     elements_[nElements_] = element; 
//     nElements_++;
// }

// template <typename T>
// void Liste<T>::modifierCapacite()
// {
//     capacite_ *= 2;
//     shared_ptr<T>* newElements = new shared_ptr<T>[capacite_];

//     for (unsigned i = 0; i < nElements_; i++)
//         newElements[i] = elements_[i];

//     delete[] elements_;
//     elements_ = newElements;
// }

// template <typename T>
// T& Liste<T>::operator[](unsigned index)
// {
//     if (index >= nElements_)
//         throw out_of_range("Index hors de portée");

//     return *elements_[index];
// }
// template <typename T>
// const T& Liste<T>::operator[](unsigned index) const
// {
//     if (index >= nElements_)
//         throw out_of_range("Index hors de portée");

//     return *elements_[index];
// }
    

// template <typename T>
// T& Liste<T>::trouver(const function<bool(const T&)>& critere)
// {
//     for (unsigned i = 0; i < nElements_; i++)
//     {
//         if (critere(*elements_[i]))
//             return *elements_[i];
//     }
//     throw runtime_error("Aucun élément trouvé");
// }
