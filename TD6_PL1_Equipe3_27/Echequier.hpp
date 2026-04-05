#pragma
#include <memory>
#include "Piece.hpp"
#include "Position.hpp"
#include <vector>
namespace Modele 
{
    class Echiquier {
    public:
        Echiquier();
        ~Echiquier();
        static const int N_CASES = 8;
    private:
        std::vector<std::vector<std::shared_ptr<Piece>>> cases_ = std::vector<std::vector<std::shared_ptr<Piece>>>(N_CASES, std::vector<std::shared_ptr<Piece>>(N_CASES, nullptr)); 
    };
    
}