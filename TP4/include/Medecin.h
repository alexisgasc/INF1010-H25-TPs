/********************************************
 * Titre: Travail pratique #1 - Medecin.h
 * Date:
 * Auteur: 
 *******************************************/

#pragma once

#include <string>
#include <iostream>
#include "Employe.h"
#include "Specialite.h"
#include "Patient.h"

using namespace std;

class Patient;

class Medecin : public Employe
{
public:
	Medecin(const string& nom, Specialite* uneSpecialite, const string& id);
	virtual ~Medecin() = default;
	Specialite * getSpecialite() const;
	void setSpecialite(Specialite* specialite);
    virtual float calculerSalaire() const = 0;
	virtual ostream &afficher(ostream &out) const;
	const shared_ptr<Patient> getPatient() const;
	void setPatient(const shared_ptr<Patient>& p);
	bool operator==(const Medecin &rhs) const;

protected:
	Specialite* specialite_;
	shared_ptr<Patient> patient_;
};
