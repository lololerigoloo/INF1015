#pragma once
#include <stdexcept>

class ExceptionNombreRoisNoirs : public std::runtime_error
{
public:
    ExceptionNombreRoisNoirs() : std::runtime_error("Il ne peut y avoir que 2 rois noirs dans une partie d'échecs !") {}
};
class ExceptionNombreRoisBlancs : public std::runtime_error
{
public:
    ExceptionNombreRoisBlancs() : std::runtime_error("Il ne peut y avoir que 2 rois blancs dans une partie d'échecs !") {}
};
class ExceptionNombrePionsBlancs : public std::runtime_error
{
public:
    ExceptionNombrePionsBlancs() : std::runtime_error("Il ne peut y avoir que 8 pions blancs dans une partie d'échecs !") {}
};
class ExceptionNombrePionsNoirs : public std::runtime_error
{
public:
    ExceptionNombrePionsNoirs() : std::runtime_error("Il ne peut y avoir que 8 pions noirs dans une partie d'échecs !") {}
};  
class ExceptionNombreFousBlancs : public std::runtime_error
{
public:    ExceptionNombreFousBlancs() : std::runtime_error("Il ne peut y avoir que 2 fous blancs dans une partie d'échecs !") {}
};
class ExceptionNombreFousNoirs : public std::runtime_error{
public:    ExceptionNombreFousNoirs() : std::runtime_error("Il ne peut y avoir que 2 fous noirs dans une partie d'échecs !") {}
};
class ExceptionNombreToursBlanches : public std::runtime_error{
public:    ExceptionNombreToursBlanches() : std::runtime_error("Il ne peut y avoir que 2 tours blanches dans une partie d'échecs !") {}
};
class ExceptionNombreToursNoires : public std::runtime_error{
public:    ExceptionNombreToursNoires() : std::runtime_error("Il ne peut y avoir que 2 tours noires dans une partie d'échecs !") {}
};

// extra j'ai pas faite mais ça peut être marrant de faire des exceptions pour les cavaliers et les reines aussi cest ez 
class ExceptionCavalierBlancs : public std::runtime_error{
public:    ExceptionCavalierBlancs() : std::runtime_error("Il ne peut y avoir que 2 cavaliers blancs dans une partie d'échecs !") {}
};
class ExceptionCavalierNoirs : public std::runtime_error{
public:    ExceptionCavalierNoirs() : std::runtime_error("Il ne peut y avoir que 2 cavaliers noirs dans une partie d'échecs !") {}
};
class ExceptionReineBlanche : public std::runtime_error{
public:    ExceptionReineBlanche() : std::runtime_error("Il ne peut y avoir qu'une reine blanche dans une partie d'échecs !") {}
};
class ExceptionReineNoire : public std::runtime_error{
public:    ExceptionReineNoire() : std::runtime_error("Il ne peut y avoir qu'une reine noire dans une partie d'échecs !") {}
};
