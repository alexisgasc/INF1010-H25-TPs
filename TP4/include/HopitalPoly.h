#pragma once

#include <string>
#include <vector>
#include "Employe.h"
#include "Medecin.h"
#include "Pediatre.h"
#include "Chirurgien.h"
#include "Cardiologue.h"
#include "Infirmier.h"
#include "Patient.h"
#include <memory>
#include <iostream>
#include "Foncteur.h"
#include <map>
#include <set>
#include <functional>

using namespace std;

class HopitalPoly
{
public:
	HopitalPoly(const string & nom);
	
	string  getNom() const;
	const vector<shared_ptr<Employe>>& getEmployes() const;
	const vector<shared_ptr<Patient>>& getPatients() const;
    void  setNom( string  nom);

	HopitalPoly &operator+=(const shared_ptr<Employe>& employe);
	HopitalPoly & operator+=(const shared_ptr<Patient>& patient);
	
	bool operator==(const HopitalPoly &rhs) const;

	Medecin *listersi(const function<bool(const Employe &employe)> &critere) const;
	void ajouterPatientAuMedecin(string &id,const shared_ptr<Patient> &patient);
	unordered_map<Medecin *, set<shared_ptr<Patient>, ComparerPersonne<Patient>>, HashEmploye> getPatientsParMedecin();
	map<TypeSoins, vector<shared_ptr<Patient>>> trouverPatientParTypeSoins();

	set<shared_ptr<Medecin>, ComparerPersonne<Medecin>> getMedecinParCritere(function<bool(const shared_ptr<Medecin> &p)> critere) const;

	float getSalaireTotal() const;

    void afficherEmploye(ostream &out) const;
	ostream& afficher(ostream &out) const;

	friend ostream &operator<<(ostream &o, const HopitalPoly &c);

private:
    string nom_;
	int chambreLibre_;
	vector<shared_ptr<Employe>> employes_;
	vector<shared_ptr<Patient>> patients_;
	unordered_map<Medecin *, set<shared_ptr<Patient>, ComparerPersonne<Patient>>, HashEmploye> medecinTousPatients_;
};
