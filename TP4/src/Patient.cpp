#include "Patient.h"

Patient::Patient(std::string nom, int age)
    : nom_(nom), age_(age), typeSoins_(TypeSoins::PAS_BESOIN), infirmier_(nullptr), medecin_(nullptr) {}

void Patient::setNom(const string& nom) {
    nom_ = nom;
}

const string& Patient::getNom() const {
    return nom_;
}

int Patient::getSalle() const {
    return numeroSalle_;
}

const TypeSoins& Patient::getTypeSoins() const {
    return typeSoins_;
}

void Patient::setTypeSoins(const TypeSoins& typeSoins) {
    typeSoins_=typeSoins;
}


shared_ptr<Infirmier> Patient::getInfirmier() const {
    return infirmier_;
}

shared_ptr<Medecin>  Patient::getMedecin() const {
    return medecin_;
}

vector<string> Patient::getAntecedentsMedicaux() const {
    return antecedentsMedicaux_;
}

void Patient::ajouterAntecedent(const std::string& antecedent) {
    antecedentsMedicaux_.push_back(antecedent);
}

void Patient::misAjourTypeSoin(const TypeSoins& typeSoin) {
    typeSoins_ = typeSoin;
}

void Patient::misAjourSalle(int nSalle) {
    numeroSalle_ = nSalle;
}

void Patient::assignerInfirmier(const shared_ptr<Infirmier>& i){
    infirmier_ = i;
}

void Patient::assignerMedecin(const shared_ptr<Medecin>& m){
    medecin_ = m;
}


void Patient::afficher(ostream& out) const {
    out << "Nom: " << nom_ << "\n";
    out << "Âge: " << age_ << " ans\n";
    out << "Numéro de salle: " << numeroSalle_ << "\n";

    out << "Type de soins requis: ";
    switch (typeSoins_) {
        case TypeSoins::CHIRURGICAL:
            out << "Chirurgie\n";
            break;
        case TypeSoins::CARDIOLOGIE:
            out << "Cardiologie\n";
            break;
        case TypeSoins::PEDIATRIE:
            out << "Pédiatrie\n";
            break;
        case TypeSoins::PAS_BESOIN:
            out << "Pas besoin de soin\n";
            break;
    }

    out << "Antécédents médicaux:\n";
    for (const auto& antecedent : antecedentsMedicaux_) {
        out << " > " << antecedent << "\n";
    }
}

ostream& operator<<(ostream& out, const Patient& p) {
    p.afficher(out);
    return out;
}