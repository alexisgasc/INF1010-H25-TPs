#include "Foncteur.h"

size_t HashEmploye::operator()(const Employe* a) const
{
    return hash<string>()(a->getId());
}