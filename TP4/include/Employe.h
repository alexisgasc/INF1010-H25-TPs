#pragma once
#include <string>
#include <iostream>

using namespace std;

class Employe {
public:
    Employe(const string& nom = "Inconnu", const string& id = "Inconnu");
    virtual ~Employe() = default;
    string getNom() const;
    string getId() const;
    void setNom(const string& nom);
    virtual float calculerSalaire() const = 0;
    virtual ostream& afficher(ostream &out) const;
    friend ostream &operator<<(ostream &out, const Employe &e);

protected:
    string nom_;
    string id_;
};

