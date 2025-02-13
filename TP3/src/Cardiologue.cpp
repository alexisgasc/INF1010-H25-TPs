#include "Cardiologue.h"

// TODO: Implémenter le constructeur de Cardiologue.
// - Initialiser le nom du cardiologue en utilisant le constructeur de la classe parente (Medecin).
// - Initialiser la spécialité avec "Cardiologie" et le niveau passé en paramètre.
// - Initialiser les attributs nbPatients_, nbConferences_, et nbPublications_ avec les valeurs passées en paramètres.
Cardiologue::Cardiologue(const string& nom, unsigned nbPatients, unsigned nbConsultations, unsigned int niveau) : {}

// TODO: Implémenter la méthode getNbPatients.
// - Retourner le nombre de patients traités par le cardiologue.
unsigned int Cardiologue::getNbPatients() const {
    return 0;
}

// TODO: Implémenter la méthode setNbPatients.
// - Mettre à jour le nombre de patients traités par le cardiologue.
void Cardiologue::setNbPatients(unsigned int nbPatients) {
}

// TODO: Implémenter la méthode getNbConferences.
// - Retourner le nombre de conférences données par le cardiologue.
unsigned int Cardiologue::getNbConferences() const {
    return 0;
}

// TODO: Implémenter la méthode setNbConferences.
// - Mettre à jour le nombre de conférences données par le cardiologue.
void Cardiologue::setNbConferences(unsigned int nbConferences) {
}

// TODO: Implémenter la méthode getNbPublications.
// - Retourner le nombre de publications du cardiologue.
unsigned int Cardiologue::getNbPublications() const {
    return 0;
}

// TODO: Implémenter la méthode ajouterPublications.
// - Ajouter un nombre de publications au total existant.
void Cardiologue::ajouterPublications(unsigned int nbPublications) {
}

// TODO: Implémenter la méthode calculerSalaire.
// - Calculer le salaire du cardiologue en fonction de son niveau, de ses patients, de ses conférences et de ses publications.
// - Exemple de calcul : salaireBase * niveau + (nbPatients * 30) + (nbConferences * 50) + (nbPublications * 200)
float Cardiologue::calculerSalaire() const {
    return 0.0f;
}

// TODO: Implémenter la méthode opererCoeur.
// - Opérer un patient et mettre à jour les informations du cardiologue et du patient.
// - Mettre à jour le nombre de patients traités.
// - Assigner le patient au cardiologue.
// - Ajouter un antécédent médical pour le patient (Examen ou traitement cardiaque effectué par Dr X.).
// - Mettre à jour le type de soins du patient.
void Cardiologue::opererCoeur(shared_ptr<Patient>& p) {
   
}

// TODO: Implémenter la méthode afficher.
// vous devez réutiliser la methode afficher de medecin
// - Afficher les informations du cardiologue, y compris son nombre de patients, de conférences et de publications.
// - Utiliser la méthode afficher de la classe parente (Medecin) pour afficher les informations de base.
ostream& Cardiologue::afficher(ostream& out) const {
    return out;
}