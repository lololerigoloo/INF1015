#pragma once 
#include "pilote.hpp"
class Copilote : public Pilote
{
    public:
        Copilote();
        ~Copilote();
    private:
    std::string _role;
    
};