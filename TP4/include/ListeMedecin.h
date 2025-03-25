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
        heapMedecin_.push_back(medecin);
        push_heap(heapMedecin_.begin(), heapMedecin_.end(), ComparerSalaire());
    }

    // TODO: Ajouter un medecin à la priority queue si le type de medecin est U ou de type Z et utiliser push_heap pour maintenir la propriété du heap avec le foncteur ComparerSalaire
    template <class U, class Z>
    void ajoutermedecin(T *medecin) {
        if (dynamic_cast<U*>(medecin) or dynamic_cast<U*>(medecin)) {
            ajouterMedecin(medecin);
        }
    }

    size_t size() const { return heapMedecin_.size(); }

    // TODO: Retourner le salaire de tous les medecins dans la liste en n'utilisant pas de boucle avec les algorithmes de la STL uniquement
    double getSalaireTotal() const
    {
        return accumulate(heapMedecin_.begin(), heapMedecin_.end(), 0.0,
            [](double& somme, const T* medecin) {
                return somme + medecin->calculerSalaire();
                }
            );
    }

    // TODO: Trouver le medecin avec le plus gros salaire en utilisant les algorithmes de la STL uniquement
    T *getMedecinAvecPlusHautSalaire() const
    {
        return heapMedecin_.front();
    }

    // TODO: Enlever le medecin avec le plus salaire de la liste et utiliser pop_heap pour maintenir la propriété du heap avec le foncteur ComparerSalaire
    T* enleverMedecinAvecPlusHautSalaire()
    {
        if (heapMedecin_.empty()) {
            return nullptr;
        }
        pop_heap(heapMedecin_.begin(), heapMedecin_.end(), ComparerSalaire());
        T* medecinAvecPlusHautSalaire = heapMedecin_.back();
        heapMedecin_.pop_back();
        return medecinAvecPlusHautSalaire;
    }

private:
    vector<T *> heapMedecin_;
};