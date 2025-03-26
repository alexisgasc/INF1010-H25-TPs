#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "Medecin.h"
#include "Infirmier.h"

using namespace std;

class Infirmier;
class Medecin;

enum class TypeSoins {
    CHIRURGICAL,
    CARDIOLOGIE,
    PEDIATRIE,
    PAS_BESOIN
};

class Patient {
public:
    Patient(std::string nom, int age);
    void setNom(const string& nom);
    const string& getNom() const;
    int getSalle() const;
    const TypeSoins& getTypeSoins() const;
    void setTypeSoins(const TypeSoins& typeSoins);
    vector<string> getAntecedentsMedicaux() const;
    shared_ptr<Infirmier> getInfirmier() const;
    shared_ptr<Medecin> getMedecin() const;
    void ajouterAntecedent(const std::string& antecedent);
    void misAjourTypeSoin(const TypeSoins& typeSoin);
    void misAjourSalle(int nSalle);
    void assignerInfirmier(const shared_ptr<Infirmier>& i);
    void assignerMedecin(const shared_ptr<Medecin>& m);
    void afficher(ostream& out) const;
    friend ostream& operator<<(ostream& out, const Patient& p);

private:
    std::string nom_;
    int age_;
    int numeroSalle_;
    TypeSoins typeSoins_;
    vector<string> antecedentsMedicaux_;
    shared_ptr<Infirmier> infirmier_;
    shared_ptr<Medecin> medecin_;
};

