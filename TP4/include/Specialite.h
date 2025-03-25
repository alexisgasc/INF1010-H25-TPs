#pragma once
#include <string>
using namespace std;
class Specialite
{
public:
	Specialite();
	Specialite(const string & domaine, unsigned int niveau);

	string getDomaine() const;
	unsigned int getNiveau() const;

	void setDomaine(const string& domaine);
	void setNiveau(unsigned int niveau);

	ostream& afficher(ostream &out) const;

	friend ostream &operator<<(ostream &out, const Specialite &b);
	bool operator==(const Specialite &rhs) const;
	Specialite(const Specialite &a);

private:
	string domaine_;
	unsigned niveau_;
};
