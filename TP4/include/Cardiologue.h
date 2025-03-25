#pragma once
#include "Medecin.h"

class Cardiologue: virtual public Medecin
{
public:
    Cardiologue(const string& nom, const string& id, unsigned nbPatients, unsigned nbConferences, unsigned int niveau = 0);
    unsigned int getNbPatients() const;
    void setNbPatients(unsigned int nbPatients);
    unsigned int getNbConferences() const;
    void setNbConferences(unsigned int nbConferences);
    unsigned int getNbPublications() const;
    void ajouterPublications(unsigned int nbPublications);
    float calculerSalaire() const override;
    void opererCoeur(shared_ptr<Patient>& p);
    
    ostream& afficher(ostream& out) const override;
private:
    const float salaireBase = 4500.0f;
    unsigned nbPatients_;
    unsigned nbConferences_;
    unsigned nbPublications_;
};