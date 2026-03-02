#pragma once
#include "pilote.hpp"

class Avion
{
    public:
        Avion();
        ~Avion();
    private:
    Pilote _pilote;
    double _vitesse;
    
};