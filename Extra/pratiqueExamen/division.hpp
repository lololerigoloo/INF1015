#include <ostream>
class Division
{
public:
    Division(int a, int b)
        : _numerateur(a), _denominateur(b) {}
    Division operator+(const Division &b) const
    {
        return {
            _numerateur * b._denominateur + b._numerateur * _denominateur,
            _denominateur * b._denominateur};
    }
    friend std::ostream &operator<<(std::ostream &os, const Division& div);

private:
    int _numerateur;
    int _denominateur;
};
std::ostream& operator<<(std::ostream& os, const Division& div) {
    return os << "(" << div._numerateur << "/" << div._denominateur << ")";
}