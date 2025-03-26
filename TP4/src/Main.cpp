#include "Pediatre.h"
#include "Chirurgien.h"
#include "Cardiologue.h"
#include "TestSuite.h"
#include "HopitalPoly.h"
#include <iostream>
#include <sstream>
#include "Foncteur.h"
#include "ListeMedecin.h"
#include "MedecinRegionEloigne.h"

using namespace std;

int main() {
    TestSuite testSuite;
    /**************************Test Liste************************************************/

    testSuite.require("Test ComparerPatient", 1.0, [&]() {
        ComparerPersonne<Patient> comparateur;
        shared_ptr<Patient> patient1 = make_shared<Patient>("Biden", 30);
        shared_ptr<Patient> patient2 = make_shared<Patient>("Winnie Da Pooh", 25);
        
        assert(comparateur(patient1, patient2) == true, "Erreur: La comparaison des patients par nom n'est pas correcte.");
        assert(comparateur(patient2, patient1) == false, "Erreur: La comparaison des patients par nom n'est pas correcte.");
    });
    
    testSuite.require("Test ComparerMedecin", 1.0, [&]() {
        ComparerPersonne<Medecin> comparateur;
        shared_ptr<Chirurgien> medecin1 = make_shared<Chirurgien>("Dr. Fauci", "ID001", 12, 5);
        shared_ptr<Pediatre> medecin2 = make_shared<Pediatre>("Dr. House", "ID002", 15, 3);
        
        assert(comparateur(medecin1, medecin2) == true, "Erreur: La comparaison des medecins par nom n'est pas correcte.");
        assert(comparateur(medecin2, medecin1) == false, "Erreur: La comparaison des medecins par nom n'est pas correcte.");
    });
    
    testSuite.require("Test HashEmploye", 1.0, [&]() {
        HashEmploye hasher;
        Infirmier infirmier1("Nightingale", "Florence", 25.0f, "ID001");
        Infirmier infirmier2("Nightingale", "Florence", 25.0f, "ID001");
        Infirmier infirmier3("Barton", "Clara", 30.0f, "ID003");
        
        size_t hash1 = hasher(&infirmier1);
        size_t hash2 = hasher(&infirmier2);
        size_t hash3 = hasher(&infirmier3);
        
        assert(hash1 == hash2, "Erreur: Le hash de deux employes identiques devrait être le même.");
        assert(hash1 != hash3, "Erreur: Le hash de deux employes differents devrait être different.");
    });

    testSuite.require("Test MedecinRegionEloigne - Constructor", 1.0, [&]() {
        MedecinRegionEloigne medecin("Dr Stephen Strange", "ID101", 5, 3);
        
        assert(medecin.getNom() == "Dr Stephen Strange", "Erreur: Le nom du medecin n'est pas correct.");
        assert(medecin.getId() == "ID101", "Erreur: L'ID du medecin n'est pas correct.");
        assert(medecin.getSpecialite()->getDomaine() == "Medecine en region eloignee", 
               "Erreur: La specialite du medecin n'est pas correcte.");
        assert(medecin.getSpecialite()->getNiveau() == 3, 
               "Erreur: Le niveau de specialite n'est pas correct.");
    });

    testSuite.require("Test MedecinRegionEloigne - Calcul du salaire", 1.0, [&]() {
        MedecinRegionEloigne medecin("Dr Stephen Strange", "ID101", 5, 3);
        
        float salaireInitial = medecin.calculerSalaire();
        float salaireAttendu = 5000.0 * 3 + 5 * 500;
        
        assert(salaireInitial == salaireAttendu, 
               "Erreur: Le calcul du salaire initial n'est pas correct.");
        
        auto patientChirurgie = make_shared<Patient>("Patient1", 40);
        patientChirurgie->setTypeSoins(TypeSoins::CHIRURGICAL);
        medecin.opererPatient(patientChirurgie);
        medecin.opererPatient(patientChirurgie);
        
        auto patientPediatrie = make_shared<Patient>("Enfant1", 8);
        patientPediatrie->setTypeSoins(TypeSoins::PEDIATRIE);
        medecin.examinerPatient(patientPediatrie);
        
        auto patientCardio = make_shared<Patient>("CardioPatient", 55);
        patientCardio->setTypeSoins(TypeSoins::CARDIOLOGIE);
        medecin.opererCoeur(patientCardio);
        
        float nouveauSalaire = medecin.calculerSalaire();
        float nouveauSalaireAttendu = 5000.0 * 3 + 5 * 500 + 2 * 30 + 1 * 50 + 1 * 20;
        
        assert(nouveauSalaire == nouveauSalaireAttendu, 
               "Erreur: Le calcul du salaire apres avoir vu des patients n'est pas correct.");
    });

    testSuite.require("Test MedecinRegionEloigne - Visiter patient en helicoptere (Chirurgie)", 1.0, [&]() {
        MedecinRegionEloigne medecin("Dr Stephen Strange", "ID101", 5, 3);
        auto patient = make_shared<Patient>("Patient Chirurgie", 45);
        patient->setTypeSoins(TypeSoins::CHIRURGICAL);
        medecin.visiterPatientEnHelicoptere(patient);
        
        assert(patient->getAntecedentsMedicaux().size() == 1,
            "Erreur: Les antecedents du patient n'ont pas ete correctement mis a jour.");
        
        string expectedAntecedent = "Transport medical par helicoptere effectue par Dr Stephen Strange.";
        assert(patient->getAntecedentsMedicaux()[0] == expectedAntecedent,
            "Erreur: Le contenu de l'antecedent medical n'est pas correct.");
        
        assert(medecin.getNbVoyagesEnHelicopteres() == 6,
            "Erreur: Le nombre de voyages en helicoptere n'a pas ete incremente.");
    });

    testSuite.require("Test MedecinRegionEloigne - Affichage", 1.0, [&]() {
        MedecinRegionEloigne medecin("Dr Stephen Strange", "ID101", 5, 3);
        ostringstream oss;
        medecin.afficher(oss);
        string output = oss.str();
        
        float salaire = 5000.0 * 3 + 5 * 500;
        string expectedOutput =
          "Nom: Dr Stephen Strange\n"
          "Id: ID101\n"
          "Domaine: Medecine en region eloignee\n"
          "Niveau: 3\n"
          "Niveau de Chirurgie: 3\n"
          "Niveau de Cardiologue: 3\n"
          "Niveau de Pediatre: 3\n"
          "Nombre de voyages en helicoptere: 5\n"
          "Salaire: " + to_string(salaire) + "\n";
        assert(output == expectedOutput,
          "Erreur: L'affichage ne correspond pas exactement a la sortie attendue.");
      });
    
    testSuite.require("Test ListeMedecin - Ajout de medecins", 1.0, [&]() {
        ListeMedecin<Cardiologue> liste;
        Cardiologue* cardiologue1 = new Cardiologue("Dr. Fauci", "ID001", 10, 5, 3);
        Cardiologue* cardiologue2 = new Cardiologue("Dr. Arruda", "ID002", 15, 7, 4);
        
        liste.ajouterMedecin(cardiologue1);
        liste.ajouterMedecin(cardiologue2);
        
        assert(liste.size() == 2, "Erreur: La taille de la liste n'est pas correcte apres l'ajout de medecins.");
        
        delete cardiologue1;
        delete cardiologue2;
    });
    
    testSuite.require("Test ListeMedecin - Ajout avec type different", 1.0, [&]() {
        ListeMedecin<Medecin> liste;
        Pediatre* pediatre = new Pediatre("Dr. DiIoia", "ID003", 8, 4);
        Cardiologue* cardiologue = new Cardiologue("Dr. Heart", "ID004", 12, 6, 3);
        Chirurgien* chirurgien = new Chirurgien("Dr. House", "ID001", 12, 5);

        liste.ajoutermedecin<Pediatre, Cardiologue>(pediatre);
        liste.ajoutermedecin<Pediatre, Cardiologue>(cardiologue);
        liste.ajoutermedecin<Pediatre, Cardiologue>(chirurgien);

        assert(liste.size() == 2, "Erreur: La liste devrait rejeter les medecins du mauvais type.");
        
        delete pediatre;
        delete cardiologue;
        delete chirurgien;
    });
    
    testSuite.require("Test ListeMedecin - Calcul du salaire total", 1.0, [&]() {
        ListeMedecin<Cardiologue> liste;
        Cardiologue* cardiologue1 = new Cardiologue("Dr. Fauci", "ID005", 10, 5, 3);
        Cardiologue* cardiologue2 = new Cardiologue("Dr. Arruda", "ID006", 15, 7, 4);
        
        liste.ajouterMedecin(cardiologue1);
        liste.ajouterMedecin(cardiologue2);
        
        double salaireTotal = liste.getSalaireTotal();
        double salaireAttendu = cardiologue1->calculerSalaire() + cardiologue2->calculerSalaire();
        
        assert(salaireTotal == salaireAttendu, "Erreur: Le calcul du salaire total n'est pas correct.");
        
        delete cardiologue1;
        delete cardiologue2;
    });
    
   testSuite.require("Test ListeMedecin - Medecin avec le plus haut salaire", 1.0, [&]() {
        ListeMedecin<Cardiologue> liste;
        Cardiologue* cardiologue1 = new Cardiologue("Dr. Fauci", "ID007", 10, 5, 3);
        Cardiologue* cardiologue2 = new Cardiologue("Dr. Arruda", "ID008", 15, 7, 4);
        
        liste.ajouterMedecin(cardiologue1);
        liste.ajouterMedecin(cardiologue2);
        
        Cardiologue* medecinPlusHautSalaire = liste.getMedecinAvecPlusHautSalaire();
        assert(medecinPlusHautSalaire == cardiologue2, "Erreur: Le medecin avec le plus haut salaire n'est pas correct.");
        
        delete cardiologue1;
        delete cardiologue2;
    });
    
    testSuite.require("Test ListeMedecin - Enlever medecin avec plus haut salaire", 1.0, [&]() {
        ListeMedecin<Cardiologue> liste;
        Cardiologue* cardiologue1 = new Cardiologue("Dr. Fauci", "ID009", 10, 5, 3);
        Cardiologue* cardiologue2 = new Cardiologue("Dr. Arruda", "ID010", 15, 7, 4);
        
        liste.ajouterMedecin(cardiologue1);
        liste.ajouterMedecin(cardiologue2);
        
        Cardiologue* medecinEnleve = liste.enleverMedecinAvecPlusHautSalaire();
        assert(medecinEnleve == cardiologue2, "Erreur: Le mauvais medecin a ete enleve.");
        assert(liste.size() == 1, "Erreur: La taille de la liste n'est pas correcte apres avoir enleve un medecin.");
        
        delete cardiologue1;
        delete cardiologue2;
    });

    testSuite.require("Test HopitalPoly - ListerSi", 1.0, [&]() {
        HopitalPoly hopital("Hopital Central");
        shared_ptr<Cardiologue> medecin1 = make_shared<Cardiologue>("Dr. Fauci", "ID007", 10, 5, 3);
        shared_ptr<Pediatre> medecin2 = make_shared<Pediatre>("Dr. Graisse", "ID002", 15, 3);
        shared_ptr<Infirmier> infirmier1 = make_shared<Infirmier>("Nightingale", "Florence", 25.0f, "ID001");

        hopital += medecin1;
        hopital += medecin2;
        hopital += infirmier1;
        
        auto resultat = hopital.listersi([](const Employe& e) { return e.getNom() == "Dr. Fauci"; });
        
        assert(resultat != nullptr, "Erreur: La recherche n'a pas trouve le medecin.");
        assert(resultat->getNom() == "Dr. Fauci", "Erreur: Le mauvais medecin a ete trouve.");
        
        auto resultatVide = hopital.listersi([](const Employe& e) { return e.getNom() == "Dr. Inexistant"; });
        assert(resultatVide == nullptr, "Erreur: La recherche a trouve un medecin inexistant.");

        auto resultatInvalide = hopital.listersi([](const Employe& e) { return e.getNom() == "Nightingale"; });
        assert(resultatInvalide == nullptr, "Erreur: La recherche a trouve un infirmier au lieu d'un medecin.");
    });

    testSuite.require("Test HopitalPoly - AjouterPatientAuMedecin", 1.0, [&]() {
        HopitalPoly hopital("Hopital Central");
    
        shared_ptr<Cardiologue> medecin = make_shared<Cardiologue>("Dr. Fauci", "ID007", 10, 5, 3);
        
        shared_ptr<Patient> patient1 = make_shared<Patient>("Patient1", 30);
        shared_ptr<Patient> patient2 = make_shared<Patient>("Patient2", 25);
        shared_ptr<Patient> patient3 = make_shared<Patient>("Graisse3", 77);

        hopital += medecin;
        hopital += patient1;
        hopital += patient2;
    
        string id = "ID007";
    
        hopital.ajouterPatientAuMedecin(id, patient1);
        hopital.ajouterPatientAuMedecin(id, patient2);
    
        auto patientsParMedecin = hopital.getPatientsParMedecin();
        
        auto medecinPtr = hopital.listersi([id](const Employe& e) { return e.getId() == id; });
    
        assert(medecinPtr != nullptr, "Erreur: Le medecin n'a pas été trouvé.");
        
        auto medecinIterator = patientsParMedecin.find(medecinPtr);
        assert(medecinIterator != patientsParMedecin.end(),
            "Erreur: Le medecin n'est pas trouve dans la map.");
    
        assert(medecinIterator->second.size() == 2,
            "Erreur: Le nombre de patients associes au medecin n'est pas correct.");
    
        auto patientIt = medecinIterator->second.begin();
        assert((*patientIt)->getNom() == "Patient1", "Erreur: Le premier patient n'est pas correct.");
        ++patientIt;
        assert((*patientIt)->getNom() == "Patient2", "Erreur: Le second patient n'est pas correct.");
    
        string idInexistant = "ID999";
        hopital.ajouterPatientAuMedecin(idInexistant, patient1);
    
        assert(medecinIterator->second.size() == 2,
            "Erreur: L'ajout avec un ID inexistant a modifie la map.");

        hopital.ajouterPatientAuMedecin(id, patient3);
    
        assert(medecinIterator->second.size() == 2,
                "Erreur: L'ajout avec un patient inexistant a modifie la map.");     
    });

    testSuite.require("Test HopitalPoly - TrouverPatientParTypeSoins", 1.0, [&]() {
        HopitalPoly hopital("Hopital Central");
        auto patient1 = make_shared<Patient>("GigaChad", 30);
        auto patient2 = make_shared<Patient>("Donald J Trump", 25);
        
        patient1->setTypeSoins(TypeSoins::CARDIOLOGIE);
        patient2->setTypeSoins(TypeSoins::PEDIATRIE);
        
        hopital+=patient1;
        hopital+=patient2;
        
        auto resultat = hopital.trouverPatientParTypeSoins();
        
        assert(resultat[TypeSoins::CARDIOLOGIE].size() == 1, "Erreur: Nombre incorrect de patients en Cardio.");
        assert(resultat[TypeSoins::PEDIATRIE].size() == 1, "Erreur: Nombre incorrect de patients en Pediatrie.");
        assert(resultat[TypeSoins::CARDIOLOGIE][0] == patient1, "Erreur: Mauvais patient classe en Cardio.");
    });

    testSuite.require("Test HopitalPoly - Affichage", 1.0, [&]() {
        HopitalPoly hopital("Hopital Central");
        shared_ptr<Cardiologue> medecin = make_shared<Cardiologue>("Dr. Fauci", "ID007", 10, 5, 3);
        hopital += medecin;
        ostringstream oss;
        hopital.afficher(oss);
        string output = oss.str();
        
        string expectedOutput = 
            "Hopital: Hopital Central\n"
            "Employes: \n"
            "Nom: Dr. Fauci\n"
            "Id: ID007\n"
            "Domaine: Cardiologie\n"
            "Niveau: 3\n"
            "Nombre de patients: 10\n"
            "Nombre de conferences: 5\n"
            "Nombre de publications: 0\n"
            "\n";
        assert(output == expectedOutput,
            "Erreur: L'affichage ne correspond pas exactement a la sortie attendue.");
    });

    testSuite.require("Test HopitalPoly - GetMedecinParNom", 1.0, [&]() {
        HopitalPoly hopital("Hopital Central");
        auto specialite = make_shared<Specialite>("Cardio", 5);
        shared_ptr<Cardiologue> medecin1 = make_shared<Cardiologue>("Dr. Fauci", "ID007", 10, 5, 3);
        shared_ptr<Chirurgien> medecin2 = make_shared<Chirurgien>("Dr. House", "ID001", 12, 5);
        
        hopital += medecin1;
        hopital += medecin2;
        
        auto critere = [](const shared_ptr<Medecin>& m) { return m->getNom() == "Dr. Fauci"; };
        auto resultat = hopital.getMedecinParCritere(critere);
        
        assert(resultat.size() == 1, "Erreur: Nombre incorrect de medecins trouves.");
        assert((*resultat.begin())->getNom() == "Dr. Fauci", "Erreur: Mauvais medecin trouve.");
    });

    testSuite.require("Test HopitalPoly - GetMedecinParSpecialite", 1.0, [&]() {
        HopitalPoly hopital("Hopital Central");
        auto specialite = make_shared<Specialite>("Cardio", 5);
        shared_ptr<Cardiologue> medecin1 = make_shared<Cardiologue>("Dr. Fauci", "ID007", 10, 5, 3);
        shared_ptr<Chirurgien> medecin2 = make_shared<Chirurgien>("Dr. House", "ID002", 12, 5);
        shared_ptr<Pediatre> medecin3 = make_shared<Pediatre>("Dr. Gerald Robotnik", "ID003", 12, 5);
        shared_ptr<Pediatre> medecin4 = make_shared<Pediatre>("Doctor Ivo Robotnik", "ID004", 12, 5);

        hopital += medecin1;
        hopital += medecin2;
        hopital += medecin3;
        hopital += medecin4;

        auto critere = [](const shared_ptr<Medecin>& m) { return m->getSpecialite()->getDomaine() == "Pediatrie"; };
        auto resultat = hopital.getMedecinParCritere(critere);
        
        assert(resultat.size() == 2, "Erreur: Nombre incorrect de medecins trouves.");
        bool foundGerald = false;
        bool foundIvo = false;
        for (const auto& medecin : resultat) {
            if (medecin->getNom() == "Dr. Gerald Robotnik") foundGerald = true;
            if (medecin->getNom() == "Doctor Ivo Robotnik") foundIvo = true;
        }
        assert(foundGerald && foundIvo, "Erreur: Les deux pediatres n'ont pas ete trouves.");
    });

    testSuite.require("Test HopitalPoly - GetSalaireTotal", 1.0, [&]() {
        HopitalPoly hopital("Hopital Central");
        shared_ptr<Cardiologue> medecin1 = make_shared<Cardiologue>("Dr. Fauci", "ID007", 10, 5, 3);
        shared_ptr<Chirurgien> medecin2 = make_shared<Chirurgien>("Dr. House", "ID001", 12, 5);
        
        hopital += medecin1;
        hopital += medecin2;
        
        float salaireTotal = hopital.getSalaireTotal();
        float salaireAttendu = medecin1->calculerSalaire() + medecin2->calculerSalaire();
        
        assert(salaireTotal == salaireAttendu, "Erreur: Le calcul du salaire total n'est pas correct.");
    });

   //Affichage des resultats des tests
    testSuite.showResults();

    return 0;
}