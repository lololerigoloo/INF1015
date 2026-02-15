#include <string>
#include <ostream>
class Joueur {
public:
    Joueur();
    Joueur(const Joueur&) = default;
    Joueur(const std::string&& nom) : score_(0), nom_(std::move(nom)) {};
    ~Joueur() = default;
    void setScore(int score) { score_ = score; }
    const int getScore() const { return score_; }
    friend std::ostream &operator<<(std::ostream &os, const Joueur &j);
    

private:
    int score_;
    std::string nom_;
};

Joueur::Joueur() : score_(0), nom_("Anonyme") {}
std::ostream &operator<<(std::ostream &os, const Joueur &j) {
    os << "Joueur: " << j.nom_ << ", Score: " << j.score_;
    return os;
}


