#include "Employe.h"
#include <uuid/uuid.h>

Employe::Employe(const string& nom, const string& id): nom_(nom), id_(id) {}

string Employe::getNom() const {
    return nom_;
}

string Employe::getId() const {
    return id_;
}

void Employe::setNom(const string& nom) {
    nom_ = nom;
}

ostream& Employe::afficher(ostream &out) const {
    out << "Nom: " << nom_ << endl;
    out << "Id: " << id_ << endl;
    return out;
}

ostream &operator<<(ostream &out, const Employe &e) {
    return e.afficher(out);
}
