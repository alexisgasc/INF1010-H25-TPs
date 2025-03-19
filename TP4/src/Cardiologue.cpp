#include "Cardiologue.h"

Cardiologue::Cardiologue(const string& nom, const string& id, unsigned nbPatients, unsigned nbConferences, unsigned int niveau)
    : Medecin(nom, new Specialite("Cardiologie", niveau),id), nbPatients_(nbPatients), nbConferences_(nbConferences), nbPublications_(0) {}

unsigned int Cardiologue::getNbPatients() const {
    return nbPatients_;
}

void Cardiologue::setNbPatients(unsigned int nbPatients) {
    nbPatients_ = nbPatients;
}

unsigned int Cardiologue::getNbConferences() const {
    return nbConferences_;
}

void Cardiologue::setNbConferences(unsigned int nbConferences) {
    nbConferences_ = nbConferences;
}

unsigned int Cardiologue::getNbPublications() const {
    return nbPublications_;
}

void Cardiologue::ajouterPublications(unsigned int nbPublications) {
    nbPublications_ += nbPublications;
}

float Cardiologue::calculerSalaire() const {
    return salaireBase * specialite_->getNiveau() + (nbPatients_ * 30) + (nbConferences_ * 50) + (nbPublications_ * 200);
}

void Cardiologue::opererCoeur(shared_ptr<Patient>& p)
{
    setNbPatients(nbPatients_ + 1);
    setPatient(p);
    p->ajouterAntecedent("Examen ou traitement cardiaque effectué par " + getNom() + ".");
    p->misAjourTypeSoin(TypeSoins::PAS_BESOIN);
}

ostream& Cardiologue::afficher(ostream& out) const {
    Medecin::afficher(out);
    out << "Nombre de patients: " << nbPatients_ << endl;
    out << "Nombre de conferences: " << nbConferences_ << endl;
    out << "Nombre de publications: " << nbPublications_ << endl;
    return out;
}
