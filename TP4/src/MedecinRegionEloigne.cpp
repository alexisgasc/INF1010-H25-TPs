#include "MedecinRegionEloigne.h"
// TODO: Implémentez le constructeur de MedecinRegionEloigne
//       - Initialisez le nom, l'ID et le nombre de voyages en hélicoptère.
//       - Appelez les constructeurs des classes parentes avec des valeurs appropriées.
MedecinRegionEloigne::MedecinRegionEloigne(const string& nom, const string& id, unsigned nbVoyagesEnHelicopteres, unsigned int niveau) :
    Medecin(nom, new Specialite("Medecine en region eloignee", niveau), id),
    Chirurgien(nom, id, 0), Cardiologue(nom, id, 0, 0), Pediatre(nom, id, 0),
    nbVoyagesEnHelicopteres_(nbVoyagesEnHelicopteres){}

unsigned MedecinRegionEloigne::getNbVoyagesEnHelicopteres() const {
    return nbVoyagesEnHelicopteres_;
}

float MedecinRegionEloigne::calculerSalaire() const
{
    return salaireBase * Chirurgien::specialite_->getNiveau() + 500 * nbVoyagesEnHelicopteres_ + 20 * Cardiologue::getNbPatients() + 30 * Chirurgien::getNbOperations() + 50 * getNbNbEnfantsSoignes();
}

void MedecinRegionEloigne::visiterPatientEnHelicoptere(shared_ptr<Patient>& p)
{
    nbVoyagesEnHelicopteres_ += 1;
    p->ajouterAntecedent("Transport medical par helicoptere effectue par " + this->Chirurgien::getNom() +".");
}
// TODO: Affichez les informations du médecin en appelant l'affichage de la classe de base.
// TODO: Affichez le niveau des différentes spécialités (chirurgie, cardiologie, pédiatrie).
// TODO: Affichez le nombre de voyages en hélicoptère et le salaire calculé.
ostream& MedecinRegionEloigne::afficher(ostream& out) const
{
    out << "Nom: " + getNom() + "\n";
    out << "Id: " + getId() + "\n";
    out << "Domaine: " << Medecin::getSpecialite()->getDomaine() << "\n";
    out << "Niveau: " << Medecin::getSpecialite()->getNiveau() << "\n";
    out << "Niveau de Chirurgie: " << Chirurgien::getSpecialite()->getNiveau() << "\n";
    out << "Niveau de Cardiologue: " << Cardiologue::getSpecialite()->getNiveau() << "\n";
    out << "Niveau de Pediatre: " << Pediatre::getSpecialite()->getNiveau() << "\n";
    out << "Nombre de voyages en helicoptere: " << getNbVoyagesEnHelicopteres() << "\n";
    out << "Salaire: " << to_string(calculerSalaire()) << "\n";
    return out;
}