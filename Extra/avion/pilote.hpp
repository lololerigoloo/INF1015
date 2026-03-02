#pragma once
#include <string>
#include <iostream>
class Pilote
{
    public:
        Pilote();
        Pilote(const std::string& nom,const std::string& prenom ,const int age, const std::string& nationalite , int experience)
            : _nom((nom)) , _prenom((prenom)), _age(age) , _nationalite((nationalite)) , _experience(experience) {}
        ~Pilote();
        friend std::ostream& operator<< (std::ostream& os , const Pilote& pilote ) ;
    private:
    std::string _nom;
    std::string _prenom;
    int _age;
    std::string _nationalite;
    int _experience;    
};