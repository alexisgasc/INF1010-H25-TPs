/********************************************
 * Titre: Travail pratique #1 - Medecin.cpp
 * Date: 25 aout 2012
 * Auteur: 
 *******************************************/

#include"Medecin.h"

Medecin::Medecin(const string& nom, Specialite * uneSpecialite, const string& id): Employe(nom, id), specialite_(uneSpecialite){}

Specialite * Medecin::getSpecialite() const
{
	return specialite_;
}

const shared_ptr<Patient> Medecin::getPatient() const{
    return patient_;
}
 
void Medecin::setSpecialite(Specialite * specialite)
{
	specialite_ = specialite;
}

void Medecin::setPatient(const shared_ptr<Patient>& p){
    patient_ = p;
}

ostream &Medecin::afficher(ostream &out) const
{  
	Employe::afficher(out);
    if (specialite_ != nullptr) {
        specialite_->afficher(out);
    } else {
        out << "Specialite: Non assignee" << endl;
    }
	return out;
}

bool Medecin::operator==(const Medecin &rhs) const{
	return nom_ == rhs.nom_ && specialite_->getDomaine() == rhs.specialite_->getDomaine() && specialite_->getNiveau() == rhs.specialite_->getNiveau();
}

