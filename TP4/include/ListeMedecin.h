#pragma once

#include <vector>
#include <algorithm>
#include <numeric>

#include "Medecin.h"
#include "Foncteur.h"

using namespace std;

// T est un type de medecin
template <class T>
class ListeMedecin
{
public:
ListeMedecin() {}

    // TODO: Ajouter un medecin au set et utiliser push_heap pour maintenir la propriété du heap avec le foncteur ComparerSalaire
    void ajouterMedecin(T *medecin)
    {
    }

    // TODO: Ajouter un medecin à la priority queue si le type de medecin est U ou de type Z et utiliser push_heap pour maintenir la propriété du heap avec le foncteur ComparerSalaire
    template <class U, class Z>
    void ajoutermedecin(T *medecin)
    {
    }

    size_t size() const { return heapMedecin_.size(); }

    // TODO: Retourner le salaire de tous les medecins dans la liste en n'utilisant pas de boucle avec les algorithmes de la STL uniquement
    double getSalaireTotal() const
    {

    }

    // TODO: Trouver le medecin avec le plus gros salaire en utilisant les algorithmes de la STL uniquement
    T *getMedecinAvecPlusHautSalaire() const
    {

    }

    // TODO: Enlever le medecin avec le plus salaire de la liste et utiliser pop_heap pour maintenir la propriété du heap avec le foncteur ComparerSalaire
    T *enleverMedecinAvecPlusHautSalaire()
    {
    }

private:
    vector<T *> heapMedecin_;
};