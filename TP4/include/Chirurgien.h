#pragma once
#include "Medecin.h"

class Chirurgien: virtual public Medecin
{
public:
    Chirurgien(const string& nom, const string& id, unsigned nbHeuresGarde,  unsigned int niveau = 0);
    unsigned getNbHeuresDeGarde() const;
    void setNbHeuresDeGarde(int nbHeuresDeGarde);
    unsigned getNbOperations() const;
    void ajouterNbOperations(unsigned nbOperations);

    float calculerSalaire() const override;
    void opererPatient(shared_ptr<Patient>& p);
    
    ostream& afficher(ostream& out) const override;
private:
    unsigned nbHeuresDeGarde_;
    unsigned nbOperations_;
    const float salaireBase = 5000.0f;
};