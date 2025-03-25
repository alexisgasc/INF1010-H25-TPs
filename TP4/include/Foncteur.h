#pragma once

#include <memory>
#include <numeric>

#include "Employe.h"
#include "Medecin.h"

using namespace std;

template <class T>
class ComparerPersonne
{
    // TODO: Implémenter l'opérateur de comparaison pour comparer les noms de deux objets de type T *
public:
    bool operator()(const shared_ptr<T> &person1, const shared_ptr<T> &person2) const {
        return person1->getNom() < person2->getNom();
    }
};


template <class T>
class ComparerSalaire
{
public:
    // TODO: Implémenter l'opérateur de comparaison pour comparer les salaires de deux objets de type T *
    bool operator()(const T *elem1, const T *elem2) const
    {
        return elem1->calculerSalaire() < elem2->calculerSalaire();
    }
};

class HashEmploye
{
public:
    size_t operator()(const Employe *a) const;
};