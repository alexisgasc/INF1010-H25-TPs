#include "HopitalPoly.h"
#include <iostream>
#include "ReseauHopital.h"

ReseauHopital::ReseauHopital(const string & nom):nom_(nom) {
}

string  ReseauHopital::getNom() const
{ return nom_;}

void  ReseauHopital::setNom(const string & nom)
{ nom_ = nom;}

size_t  ReseauHopital::getNumbHospitals()
{ return tableauHopitaux_.size();}

ostream& ReseauHopital::afficher(ostream & out) const
{
	out << "Nom du reseau d'hopital: " << this->getNom() << '\n';
	for (auto &h : tableauHopitaux_) 
		h->afficher(out);
	return out;
}

bool ReseauHopital::chercherHopital(const HopitalPoly* hopital) const
{
	for(auto &h : tableauHopitaux_){
		if(*h.get() == *hopital)
		return true;
	}
	return false;
}

ReseauHopital& ReseauHopital::operator+=(unique_ptr<HopitalPoly>& hopital)
{
	if (!chercherHopital(hopital.get())) {
		tableauHopitaux_.push_back(make_unique<HopitalPoly>(*hopital));
	}
	return *this;
}

ReseauHopital& ReseauHopital::operator-=(string& nomHopital)
{
	for (int i = 0; i < int(tableauHopitaux_.size()); i++) {
		if (tableauHopitaux_[i]->getNom() == nomHopital) {
			tableauHopitaux_[i] = std::move(tableauHopitaux_.back());
			tableauHopitaux_.pop_back();
		}
	}
	return *this;
}

ostream& operator<<(ostream& o, const ReseauHopital& c)
{
	return c.afficher(o);
}
