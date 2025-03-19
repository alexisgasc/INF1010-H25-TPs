#include "HopitalPoly.h"
#include <algorithm>
HopitalPoly::HopitalPoly(const string & nom) : nom_(nom), chambreLibre_(0) {}

string HopitalPoly::getNom() const {
    return nom_;
}

const vector<shared_ptr<Employe>>& HopitalPoly::getEmployes() const {
	return employes_;
}

const vector<shared_ptr<Patient>>& HopitalPoly::getPatients() const {
    return patients_;
}

void HopitalPoly::setNom(string nom) {
    nom_ = nom;
}

HopitalPoly& HopitalPoly::operator+=(const shared_ptr<Employe>& employe) {
	employes_.push_back(employe);
    return *this;
}

HopitalPoly& HopitalPoly::operator+=(const shared_ptr<Patient>& patient) {
	patients_.push_back(patient);
    return *this;
}

bool HopitalPoly::operator==(const HopitalPoly& rhs) const {
	return nom_ == rhs.nom_;
}


// TODO: compléter la méthode trouverPatientParTypeSoins pour qu'elle retourne un map de  patient par catégorie de type de soin, ne pas utiliser de for loop et utiliser les algorithmes de la STL
map<TypeSoins, vector<shared_ptr<Patient>>> HopitalPoly::trouverPatientParTypeSoins()
{

}

// TODO: compléter la méthode getMedecinParCritere pour qu'elle retourne un set de Medecin qui respecte le critère, ne pas utiliser de for loop et utiliser les algorithmes de la STL
set<shared_ptr<Medecin>, ComparerPersonne<Medecin>> HopitalPoly::getMedecinParCritere(function<bool(const shared_ptr<Medecin>&)> critere) const {

}

// // TODO: compléter la méthode listersi pour qu'elle retourne un pointeur sur le premier medecin qui respecte le critère
Medecin *HopitalPoly::listersi(const function<bool(const Employe &employe)> &critere) const
{

}

// TODO: compléter la méthode ajouterPatientAuMedecin pour qu'elle ajoute un patient à un medecin dans la map medecinTousPatients_, ne pas utiliser de for loop et utiliser les algorithmes de la STL

void HopitalPoly::ajouterPatientAuMedecin(string &id,const shared_ptr<Patient> &patient){

}

unordered_map<Medecin *, set<shared_ptr<Patient>, ComparerPersonne<Patient>>, HashEmploye> HopitalPoly::getPatientsParMedecin()
{
	return medecinTousPatients_;
}

// TODO: compléter la méthode getSalaireTotal pour qu'elle retourne le salaire total dans l'hopital, ne pas utiliser de for loop et utiliser les algorithmes de la STL
float HopitalPoly::getSalaireTotal() const {
}

// TODO: afficher les employes, ne pas utiliser de for loop et utiliser les algorithmes de la STL
void HopitalPoly::afficherEmploye(ostream& out) const {
}

ostream& HopitalPoly::afficher(ostream &out) const {
    out << "Hopital: " << nom_ << endl;
    out << "Employes: " << endl;
    afficherEmploye(out);
    return out;
}

ostream &operator<<(ostream &o, const HopitalPoly &h) {
    return h.afficher(o);
}
