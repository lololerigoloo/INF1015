#include <iostream>
#include <string>
#include "avion.hpp"
#include "pilote.hpp"
#include <memory>
using namespace std;

int main()
{

    auto laurent = std::make_unique<Pilote>(
        "Corbeil",
        "Laurent",
        20,
        "Quebecois",
        5);
    cout <<*laurent;
}