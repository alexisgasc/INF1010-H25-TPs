#pragma once
#include "Pediatre.h"
#include "Chirurgien.h"
#include "Cardiologue.h"
class MedecinRegionEloigne: public Chirurgien, public Pediatre, public Cardiologue
{
public:
    MedecinRegionEloigne(const string& nom, const string& id, unsigned nbVoyagesEnHelicopteres,  unsigned int niveau = 0);
    float calculerSalaire() const override;
    void visiterPatientEnHelicoptere(shared_ptr<Patient>& p);
    unsigned getNbVoyagesEnHelicopteres();
    ostream& afficher(ostream& out) const override;
private:
    unsigned nbVoyagesEnHelicopteres_;
    const float salaireBase = 5000.0f;
};