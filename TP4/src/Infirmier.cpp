#include "Infirmier.h"
#include <iostream>

int Infirmier::nTypeSoin_ = 0;

Infirmier::Infirmier(const string & nom,
                    const std::string & prenom, 
					const float & tauxHoraire, const string & id):
					Employe(nom, id), prenom_(prenom), tauxHoraire_(tauxHoraire)
{  
    heuresTravaillees_  = 0;
}

Infirmier::Infirmier(const Infirmier &a): Employe(a.nom_, a.id_), prenom_(a.prenom_), tauxHoraire_(a.tauxHoraire_), 
                                            heuresTravaillees_(a.heuresTravaillees_){}

string Infirmier::getPrenom() const
{
	return prenom_;
}

vector<string> Infirmier::getListeChambre() const{
    return listeChambre_;
}

float Infirmier::getTauxHoraire() const{
	 return tauxHoraire_;
}

const shared_ptr<Patient> Infirmier::getPatient() const{
    return patient_;
}

void Infirmier::setPrenom (const string& prenom)
{
	prenom_ = prenom;
}

void Infirmier::setTauxHoraire (const float& taux)
{
	tauxHoraire_ = taux;
}

void Infirmier::setPatient(const shared_ptr<Patient>& p){
    patient_ = p;
}

unsigned Infirmier::getHeuresTravaillees() const{
    return heuresTravaillees_;
}

void Infirmier::operator+=(int numeroSalle){
    listeChambre_.push_back(std::to_string(numeroSalle));
}


void Infirmier::ajouterHeuresTravaillees(unsigned heures){
    heuresTravaillees_+= heures;
}  
  
float  Infirmier::calculerSalaire() const {
	float salaire = heuresTravaillees_ * tauxHoraire_ + listeChambre_.size() * tauxHoraire_ / 20.0;
	return  salaire;
}

ostream &Infirmier::afficher(ostream &out) const
{
	Employe::afficher(out);
    out << "Prenom: " << prenom_ << endl;
    out << "Taux horaire: " << tauxHoraire_ << " $/h" << endl;
    out << "Heures travaillees: " << heuresTravaillees_ << " heures" << endl;
    out << "Liste des chambres: ";
    if (listeChambre_.empty()) {
        out << "Aucune chambre assignee.";
    } else {
        for (const auto& chambre : listeChambre_) {
            out << chambre << " ";
        }
    }
    out << endl;
    return out;
}

bool Infirmier::operator==(const Infirmier &rhs) const{
    return nom_ == rhs.nom_ && prenom_ == rhs.prenom_;
}
