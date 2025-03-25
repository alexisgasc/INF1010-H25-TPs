#pragma once
#include <string>
#include <vector>
#include "Employe.h"
#include "Patient.h"
using namespace std;

class Patient;

class Infirmier : public Employe
{
public:
	Infirmier(const string& nom ="Inconnu", 
	          const string& prenom ="Inconnu", 
			  const float & tauxHoraire =0.0, const string& id ="Inconnu");
	Infirmier(const Infirmier &a);

	string getPrenom() const;
    float getTauxHoraire() const;
	vector<string> getListeChambre() const;
	const shared_ptr<Patient> getPatient() const ;

	void setPrenom(const string& prenom);
    void setTauxHoraire (const float & tauxHoraire);

    bool chercherChambre (const string & nbChambre) const;
    
	unsigned getHeuresTravaillees() const;
	void ajouterHeuresTravaillees(unsigned heures);  
    
	float  calculerSalaire() const override;
	void setPatient(const shared_ptr<Patient>& p);
	ostream& afficher(ostream &out) const;
	void operator+=(int numeroSalle);
	bool operator==(const Infirmier &rhs) const;

private:
	string prenom_;
	float tauxHoraire_;
	unsigned heuresTravaillees_;
	shared_ptr<Patient> patient_;
	vector<string> listeChambre_;
	static int nTypeSoin_;
};


