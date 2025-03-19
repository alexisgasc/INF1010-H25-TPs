#include "Pediatre.h"

Pediatre::Pediatre(const string& nom,const string& id, unsigned nbNbEnfantsSoignes, unsigned int niveau)
    : Medecin(nom, new Specialite("Pediatrie", niveau), id), nbEnfantsSoignes_(nbNbEnfantsSoignes) {}

void Pediatre::setNbEnfantsSoignes(int nbEnfantsSoignes) {
    nbEnfantsSoignes_ = nbEnfantsSoignes;
}

unsigned Pediatre::getNbNbEnfantsSoignes() const {
    return nbEnfantsSoignes_;
}

void Pediatre::examinerPatient(shared_ptr<Patient> &p)
{
    setNbEnfantsSoignes(nbEnfantsSoignes_ + 1);
    setPatient(p);
    p->misAjourTypeSoin(TypeSoins::PAS_BESOIN);
    p->ajouterAntecedent("Examen pédiatrique effectué par " + getNom() + ".");
}

vector<string> Pediatre::getCertifications() const {
    return certifications_;
}

Pediatre & Pediatre::operator+=(const string& certification) {
    certifications_.push_back(certification);
    return *this;
}

float Pediatre::calculerSalaire() const {
    return  salaireBase * specialite_->getNiveau() + (nbEnfantsSoignes_ * 100) + (certifications_.size() * 25);
}

ostream& Pediatre::afficher(ostream& out) const {
    Medecin::afficher(out);
    out << "Nombre d'enfants soignés: " << nbEnfantsSoignes_ << endl;
    out << "Mes certifications sont:" << endl;
    for (auto& cert : certifications_) {
        out << "> " << cert << endl;
    }
    return out;
}
