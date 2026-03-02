#include "pilote.hpp"
using namespace std;

std::ostream& operator<<(std::ostream& os, const Pilote& pilote)
{
    os << "Nous avons le pilot : " << pilote._nom << " "
       << pilote._prenom << " " << endl
       << "Ce pilote est agee de : " <<  pilote._age << " ans " << endl
       << "il a aussi "<< pilote._experience << " ans d'experience comme pilote \nFinalment ce pilote nous viens tout droit de : "
       << pilote._nationalite;

    return os;
} 
Pilote::~Pilote()
{
    
}