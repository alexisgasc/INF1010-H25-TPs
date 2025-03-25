#include "Specialite.h"
#include <iostream>

Specialite::Specialite(): domaine_(""), niveau_(0)
{
}

Specialite::Specialite(const string & domaine, unsigned niveau):
            domaine_(domaine), niveau_(niveau)
{
}

std::string Specialite::getDomaine() const
{
	return domaine_;
}

unsigned int Specialite::getNiveau() const
{
	return niveau_;
}

void Specialite::setDomaine(const std::string & domaine)
{
	domaine_ = domaine;
}

void Specialite::setNiveau(unsigned int niveau)
{
	niveau_ = niveau;
}

ostream &Specialite::afficher(ostream &out) const
{
	out << "Domaine: " << domaine_ << endl;
    out << "Niveau: " << niveau_ << endl;
	return out;
}

ostream &operator<<(ostream &out, const Specialite &b){
	return b.afficher(out);
}

bool Specialite::operator==(const Specialite &rhs) const{
	return niveau_ == rhs.niveau_ && domaine_ == rhs.domaine_;
}

Specialite::Specialite(const Specialite &a):domaine_(a.domaine_), niveau_(a.niveau_){}
