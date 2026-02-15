#include <memory>
#include <ostream>
template <typename T>
class Matrice
{
public:
    Matrice(unsigned lignes, unsigned colonnes);
    ~Matrice() = default;
    Matrice(const Matrice &other);
    T& operator()(unsigned i, unsigned j);
    void Aggrandir(unsigned newLignes, unsigned newColonnes);

    template <typename U>
    friend std::ostream &operator<<(std::ostream &, const Matrice<U> &);

private:
    unsigned lignes_;
    unsigned colonnes_;
    std::shared_ptr<T[]> data_;
};

template <typename T>
Matrice<T>::Matrice(unsigned lignes, unsigned colonnes)
{
    lignes_ = lignes;
    colonnes_ = colonnes;
    data_ = std::make_shared<T[]>(lignes * colonnes);
}
template <typename T>
Matrice<T>::Matrice(const Matrice &other)
{
    lignes_ = other.lignes_;
    colonnes_ = other.colonnes_;
    data_ = std::make_shared<T[]>(lignes_ * colonnes_);
    for (unsigned i = 0; i < lignes_ * colonnes_; ++i)
    {
        data_[i] = other.data_[i];
    }
}
template <typename T>
T &Matrice<T>::operator()(unsigned i, unsigned j)
{
    return data_[i * colonnes_ + j];
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const Matrice<T> &m)
{
    for (unsigned i = 0; i < m.lignes_; ++i)
    {
        for (unsigned j = 0; j < m.colonnes_; ++j)
        {
            os << m.data_[i * m.colonnes_ + j] << " ";
        }
        os << std::endl;
    }
    return os;
}
template <typename T>
void Matrice<T>::Aggrandir(unsigned newLignes, unsigned newColonnes)
{
    if (newLignes <= lignes_ && newColonnes <= colonnes_)
        return; // Pas besoin d'aggrandir

    std::shared_ptr<T[]> newData = std::make_shared<T[]>(newLignes * newColonnes);

    // Copier les anciennes données dans la nouvelle matrice
    for (unsigned i = 0; i < lignes_; ++i)
    {
        for (unsigned j = 0; j < colonnes_; ++j)
        {
            newData[i * newColonnes + j] = data_[i * colonnes_ + j];
        }
    }

    // Mettre à jour les dimensions et les données
    lignes_ = newLignes;
    colonnes_ = newColonnes;
    data_ = newData;
}