#include "Liste.h"
#include "Pediatre.h"
#include "Chirurgien.h"
#include "Cardiologue.h"
#include "TestSuite.h"
#include "HopitalPoly.h"
#include <memory>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
    TestSuite testSuite;

    // Création des médecins pour les tests
    shared_ptr<Pediatre> pediatre = make_shared<Pediatre>("Dr. Smith", 10, 5);
    shared_ptr<Chirurgien> chirurgien = make_shared<Chirurgien>("Dr. House", 20, 3);
    shared_ptr<Cardiologue> cardiologue = make_shared<Cardiologue>("Dr. Brown", 15, 7);


    //**************************Test Liste************************************************/

    testSuite.require("Ajout d'un médecin à la liste", 1.0, [&]() {
        Liste<shared_ptr<Medecin>> listeMedecins;
        listeMedecins += pediatre;
        assert(listeMedecins.size() == 1, "Erreur: la taille de la liste devrait être 1 après l'ajout d'un médecin.");
        assert(listeMedecins.chercher("Dr. Smith") != -1, "Erreur: le médecin ajouté n'a pas été trouvé dans la liste.");
        });

    testSuite.require("Ajout d'un médecin en double", 1.0, [&]() {
        Liste<shared_ptr<Medecin>> listeMedecins;
        listeMedecins += pediatre;
        listeMedecins += pediatre; // Ajout en double
        assert(listeMedecins.size() == 1, "Erreur: la taille de la liste ne devrait pas changer après l'ajout d'un médecin en double.");
        });

    testSuite.require("Suppression d'un médecin par objet", 1.0, [&]() {
        Liste<shared_ptr<Medecin>> listeMedecins;
        listeMedecins += pediatre;
        listeMedecins += chirurgien;
        listeMedecins -= chirurgien; // Suppression par objet
        assert(listeMedecins.size() == 1, "Erreur: la taille de la liste devrait être 1 après la suppression d'un médecin.");
        assert(listeMedecins.chercher("Dr. House") == -1, "Erreur: le médecin supprimé est toujours présent dans la liste.");
        });

    testSuite.require("Suppression d'un médecin par nom", 1.0, [&]() {
        Liste<shared_ptr<Medecin>> listeMedecins;
        listeMedecins += pediatre;
        listeMedecins += cardiologue;
        listeMedecins -= "Dr. Brown"; // Suppression par nom
        assert(listeMedecins.size() == 1, "Erreur: la taille de la liste devrait être 1 après la suppression d'un médecin par nom.");
        assert(listeMedecins.chercher("Dr. Brown") == -1, "Erreur: le médecin supprimé est toujours présent dans la liste.");
        });

    testSuite.require("Suppression d'un médecin inexistant", 1.0, [&]() {
        Liste<shared_ptr<Medecin>> listeMedecins;
        listeMedecins += pediatre;
        listeMedecins -= "Dr. Inconnu"; // Suppression d'un médecin inexistant
        assert(listeMedecins.size() == 1, "Erreur: la taille de la liste ne devrait pas changer après la suppression d'un médecin inexistant.");
        });

    testSuite.require("Recherche d'un médecin par objet", 1.0, [&]() {
        Liste<shared_ptr<Medecin>> listeMedecins;
        listeMedecins += pediatre;
        listeMedecins += chirurgien;
        assert(listeMedecins.chercher(pediatre) != -1, "Erreur: le médecin n'a pas été trouvé dans la liste par objet.");
        });

    testSuite.require("Accès à un médecin par index", 1.0, [&]() {
        Liste<shared_ptr<Medecin>> listeMedecins;
        listeMedecins += pediatre;
        listeMedecins += chirurgien;
        shared_ptr<Medecin> medecin = listeMedecins[0];
        assert(medecin->getNom() == "Dr. Smith", "Erreur: le médecin à l'index 0 n'est pas celui attendu.");
        });

    testSuite.require("Taille de la liste", 1.0, [&]() {
        Liste<shared_ptr<Medecin>> listeMedecins;
        listeMedecins += pediatre;
        listeMedecins += chirurgien;
        listeMedecins += cardiologue;
        assert(listeMedecins.size() == 3, "Erreur: la taille de la liste devrait être 3 après l'ajout de trois médecins.");
        });

    testSuite.require("Ajout d'une autre liste", 1.0, [&]() {
        Liste<shared_ptr<Medecin>> listeMedecins1;
        listeMedecins1 += pediatre;
        listeMedecins1 += chirurgien;

        Liste<shared_ptr<Medecin>> listeMedecins2;
        listeMedecins2 += cardiologue;

        listeMedecins1 += listeMedecins2; // Ajout d'une autre liste
        assert(listeMedecins1.size() == 3, "Erreur: la taille de la liste devrait être 3 après l'ajout d'une autre liste.");
        assert(listeMedecins1.chercher("Dr. Brown") != -1, "Erreur: le médecin de la deuxième liste n'a pas été ajouté.");
        });

    testSuite.require("Suppression d'une autre liste", 1.0, [&]() {
        Liste<shared_ptr<Medecin>> listeMedecins1;
        listeMedecins1 += pediatre;
        listeMedecins1 += chirurgien;
        listeMedecins1 += cardiologue;

        Liste<shared_ptr<Medecin>> listeMedecins2;
        listeMedecins2 += pediatre;
        listeMedecins2 += cardiologue;

        listeMedecins1 -= listeMedecins2; // Suppression d'une autre liste
        assert(listeMedecins1.size() == 1, "Erreur: la taille de la liste devrait être 1 après la suppression d'une autre liste.");
        assert(listeMedecins1.chercher("Dr. House") != -1, "Erreur: le médecin restant n'est pas celui attendu.");
        });

    testSuite.require("Recherche d'un objet inexistant", 1.0, [&]() {
        Liste<shared_ptr<Medecin>> listeMedecins;
        listeMedecins += pediatre;

        shared_ptr<Medecin> medecinInexistant = make_shared<Cardiologue>("Dr. Inconnu", 0, 0);
        assert(listeMedecins.chercher(medecinInexistant) == -1, "Erreur: la recherche d'un objet inexistant devrait retourner -1.");
        });

    testSuite.require("Suppression d'une liste vide", 1.0, [&]() {
        Liste<shared_ptr<Medecin>> listeMedecins1;
        listeMedecins1 += pediatre;

        Liste<shared_ptr<Medecin>> listeMedecins2; // Liste vide

        listeMedecins1 -= listeMedecins2; // Suppression d'une liste vide
        assert(listeMedecins1.size() == 1, "Erreur: la taille de la liste ne devrait pas changer après la suppression d'une liste vide.");
        });


    //*********************************Test Patient***********************************/

    testSuite.require("Ajout d'un antécédent médical", 1.0, [&]() {
        Patient patient("John Doe", 30);
        patient.ajouterAntecedent("Allergie aux arachides");
        patient.ajouterAntecedent(""); // Ajout d'un antécédent vide

        vector<string> antecedents = patient.getAntecedentsMedicaux();
        assert(antecedents.size() == 2, "Erreur: Le nombre d'antécédents médicaux n'est pas correct.");
        assert(antecedents[0] == "Allergie aux arachides", "Erreur: Le premier antécédent n'est pas correct.");
        assert(antecedents[1] == "", "Erreur: L'antécédent vide n'a pas été ajouté correctement.");
        });

    testSuite.require("Mise à jour du type de soins", 1.0, [&]() {
        Patient patient("John Doe", 30);
        patient.misAjourTypeSoin(TypeSoins::CHIRURGICAL);
        assert(patient.getTypeSoins() == TypeSoins::CHIRURGICAL, "Erreur: Le type de soins n'a pas été mis à jour correctement.");
        });

    testSuite.require("Mise à jour du numéro de salle", 1.0, [&]() {
        Patient patient("John Doe", 30);
        patient.misAjourSalle(101);
        assert(patient.getSalle() == 101, "Erreur: Le numéro de salle n'a pas été mis à jour correctement.");
        });

    testSuite.require("Assignation d'un infirmier", 1.0, [&]() {
        Patient patient("John Doe", 30);
        shared_ptr<Infirmier> infirmier = make_shared<Infirmier>("Jane", "Doe", 25.0f);

        patient.assignerInfirmier(infirmier);
        assert(patient.getInfirmier() == infirmier, "Erreur: L'infirmier n'a pas été assigné correctement.");

        patient.assignerInfirmier(nullptr);
        assert(patient.getInfirmier() == nullptr, "Erreur: L'infirmier nullptr n'a pas été assigné correctement.");
        });

    testSuite.require("Affichage d'un patient", 1.0, [&]() {
        Patient patient("John Doe", 30);
        patient.misAjourSalle(101);
        patient.misAjourTypeSoin(TypeSoins::CARDIOLOGIE);

        ostringstream oss;
        streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
        oss << patient;
        cout.rdbuf(oldCout);

        string output = oss.str();
        string expectedOutput =
            "Nom: John Doe\n"
            "Âge: 30 ans\n"
            "Numéro de salle: 101\n"
            "Type de soins requis: Cardiologie\n"
            "Antécédents médicaux:\n";

        assert(output == expectedOutput, "Erreur: Le format de l'affichage du patient est incorrect.");
        });

    testSuite.require("Affichage d'un patient avec des antécédents médicaux", 1.0, [&]() {
        Patient patient("John Doe", 30);
        patient.misAjourSalle(101);
        patient.misAjourTypeSoin(TypeSoins::CARDIOLOGIE);
        patient.ajouterAntecedent("Allergie aux arachides");
        patient.ajouterAntecedent("Hypertension");

        ostringstream oss;
        streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
        oss << patient;
        cout.rdbuf(oldCout);

        string output = oss.str();
        string expectedOutput =
            "Nom: John Doe\n"
            "Âge: 30 ans\n"
            "Numéro de salle: 101\n"
            "Type de soins requis: Cardiologie\n"
            "Antécédents médicaux:\n"
            " > Allergie aux arachides\n"
            " > Hypertension\n";

        assert(output == expectedOutput, "Erreur: Le format de l'affichage du patient avec des antécédents est incorrect.");
        });


    //*************************Test pediatre*******************************//

    testSuite.require("Initialisation d'un Pediatre", 1.0, [&]() {
        Pediatre pediatre("Dr. Green", 5, 3);
        assert(pediatre.getNbNbEnfantsSoignes() == 5, "Erreur: Le nombre d'enfants soignés initial est incorrect.");
        assert(pediatre.getCertifications().empty(), "Erreur: Les certifications doivent être vides au départ.");
        assert(pediatre.getSpecialite()->getDomaine() == "Pediatrie" && pediatre.getSpecialite()->getNiveau() == 3, "Erreur: La spécialité du pédiatre n'est pas correcte");
        });

    testSuite.require("Modification du nombre d'enfants soignés", 1.0, [&]() {
        Pediatre pediatre("Dr. Smith", 10, 5);
        pediatre.setNbEnfantsSoignes(15);
        assert(pediatre.getNbNbEnfantsSoignes() == 15, "Erreur: Le nombre d'enfants soignés n'a pas été mis à jour correctement.");
        });

    testSuite.require("Ajout de certifications", 1.0, [&]() {
        Pediatre pediatre("Dr. Smith", 10, 5);
        pediatre += "Certificat A";
        pediatre += "Certificat B";
        vector<string> certifications = pediatre.getCertifications();
        assert(certifications.size() == 2, "Erreur: Le nombre de certifications n'est pas correct.");
        assert(certifications[0] == "Certificat A", "Erreur: La première certification n'est pas correcte.");
        assert(certifications[1] == "Certificat B", "Erreur: La deuxième certification n'est pas correcte.");
        });

    testSuite.require("Calcul du salaire d'un pédiatre", 1.0, [&]() {
        Pediatre pediatre("Dr. Smith", 10, 5);
        pediatre += "Certificat A";
        pediatre += "Certificat B";
        float salaire = pediatre.calculerSalaire();
        float salaireAttendu = 16050;
        assert(salaire == salaireAttendu, "Erreur: Le calcul du salaire est incorrect.");
        });

    testSuite.require("Affichage d'un pédiatre", 1.0, [&]() {
        Pediatre pediatre("Dr. Smith", 10, 5);
        pediatre += "Certificat A";
        pediatre += "Certificat B";

        ostringstream oss;
        streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
        oss << pediatre;
        cout.rdbuf(oldCout);

        string output = oss.str();
        string expectedOutput =
            "Nom: Dr. Smith\n"
            "Domaine: Pediatrie\n"
            "Niveau: 5\n"
            "Nombre d'enfants soignés: 10\n"
            "Mes certifications sont:\n"
            "> Certificat A\n"
            "> Certificat B\n";

        assert(output == expectedOutput, "Erreur: le format de l'affichage de l'infirmier est incorrect");
        });

    testSuite.require("Assignation du médecin au patient", 1.0, [&]() {
        Pediatre pediatre("Dr. Green", 5, 3);
        shared_ptr<Patient> patient = make_shared<Patient>("John Doe", 5);
        pediatre.examinerPatient(patient);
        assert(pediatre.getNbNbEnfantsSoignes() == 6, "Erreur: Le nombre d'enfants soignés n'a pas été mis à jour.");
        assert(patient->getTypeSoins() == TypeSoins::PAS_BESOIN, "Erreur: Le type de soins du patient n'est pas correctement mis à jour.");
        assert(patient->getAntecedentsMedicaux()[0] == "Examen pédiatrique effectué par Dr. Green.", "Erreur: Les antécedents du patient n'ont pas été mis à jour correctement.");
        });

    testSuite.require("Égalité entre deux pédiatres", 1.0, [&]() {
        Pediatre pediatre1("Dr. Green", 5, 3);
        Pediatre pediatre2("Dr. Green", 5, 3);
        assert(pediatre1 == pediatre2, "Erreur: Deux pédiatres identiques ne sont pas égaux.");
        });

    //**********************************Test Chirurgien************************************/

    testSuite.require("Initialisation Churirgien", 1.0, [&]() {
        Chirurgien chirurgien("Dr. House", 20);
        assert(chirurgien.getNbHeuresDeGarde() == 20, "Erreur: Les heures de garde n'ont pas été mises à jour correctement.");
        assert(chirurgien.getSpecialite()->getDomaine() == "Chirurgie" && chirurgien.getSpecialite()->getNiveau() == 0, "Erreur: Specialité chirurgien non correcte");
        });

    testSuite.require("Modification des heures de garde", 1.0, [&]() {
        Chirurgien chirurgien("Dr. House", 20, 3);
        chirurgien.setNbHeuresDeGarde(30);
        assert(chirurgien.getNbHeuresDeGarde() == 30, "Erreur: Les heures de garde n'ont pas été mises à jour correctement.");
        });

    testSuite.require("Ajout d'opérations", 1.0, [&]() {
        Chirurgien chirurgien("Dr. House", 20, 3);
        chirurgien.ajouterNbOperations(5);
        assert(chirurgien.getNbOperations() == 5, "Erreur: Le nombre d'opérations n'a pas été mis à jour correctement.");
        });

    testSuite.require("Calcul du salaire d'un chirurgien", 1.0, [&]() {
        Chirurgien chirurgien("Dr. House", 20, 3);
        chirurgien.ajouterNbOperations(5);
        float salaire = chirurgien.calculerSalaire();
        float salaireAttendu = 15650;
        assert(salaire == salaireAttendu, "Erreur: Le calcul du salaire est incorrect.");
        });

    testSuite.require("Opération sur un patient", 1.0, [&]() {
        Chirurgien chirurgien("Dr. House", 20, 3);
        shared_ptr<Patient> patient = make_shared<Patient>("John Doe", 30);
        patient->ajouterAntecedent("");
        patient->ajouterAntecedent("");
        patient->ajouterAntecedent("");

        chirurgien.opererPatient(patient);

        assert(chirurgien.getNbOperations() == 1, "Erreur: Le nombre d'opérations n'a pas été incrémenté correctement.");
        assert(patient->getTypeSoins() == TypeSoins::PAS_BESOIN, "Erreur: Le type de soins du patient n'a pas été mis à jour correctement.");
        assert(chirurgien.getPatient() == patient, "Erreur: le patient n'a pas été correctement assigné au medecin.");
        assert(patient->getAntecedentsMedicaux()[3] == "Opération chirurgicale effectuée par Dr. House.", "Erreur: Les antédecedants du patient n'ont pas été correctement mis à jour.");
        });

    testSuite.require("Affichage d'un chirurgien", 1.0, [&]() {
        Chirurgien chirurgien("Dr. House", 20, 3);
        chirurgien.ajouterNbOperations(5);

        ostringstream oss;
        streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
        oss << chirurgien;
        cout.rdbuf(oldCout);

        string output = oss.str();
        string expectedOutput =
            "Nom: Dr. House\n"
            "Domaine: Chirurgie\n"
            "Niveau: 3\n"
            "Heures de garde: 20\n"
            "Opérations: 5\n";

        assert(output == expectedOutput, "Erreur: le format de l'affichage du chirurgien est incorrect");
        });

    //**************************Test Cardiologue****************************/

    testSuite.require("Initialisation de la spécialité d'un cardiologue", 1.0, [&]() {
        Cardiologue cardiologue("Dr. Brown", 10, 5, 3);
        assert(cardiologue.getSpecialite()->getDomaine() == "Cardiologie", "Erreur: La spécialité n'a pas été correctement initialisée.");
        assert(cardiologue.getSpecialite()->getNiveau() == 3, "Erreur: Le niveau de la spécialité n'a pas été correctement initialisé.");
        });

    testSuite.require("Calcul du salaire d'un cardiologue", 1.0, [&]() {
        Cardiologue cardiologue("Dr. Brown", 15, 7, 4);
        cardiologue.ajouterPublications(3);
        float salaire = cardiologue.calculerSalaire();
        float salaireAttendu = 19400;
        assert(salaire == salaireAttendu, "Erreur: Le calcul du salaire est incorrect.");
        });

    testSuite.require("Affichage d'un cardiologue", 1.0, [&]() {
        Cardiologue cardiologue("Dr. Brown", 15, 7, 4);
        cardiologue.ajouterPublications(3);

        ostringstream oss;
        streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
        oss << cardiologue;
        cout.rdbuf(oldCout);

        string output = oss.str();
        string expectedOutput =
            "Nom: Dr. Brown\n"
            "Domaine: Cardiologie\n"
            "Niveau: 4\n"
            "Nombre de patients: 15\n"
            "Nombre de conférences: 7\n"
            "Nombre de publications: 3\n";

        assert(output == expectedOutput, "Erreur: le format de l'affichage du cardiologue est incorrect");
        });

    testSuite.require("Test de la méthode opererCoeur", 1.0, [&]() {
        Cardiologue cardiologue("Dr. Brown", 10, 5, 3);
        shared_ptr<Patient> patient = make_shared<Patient>("John Doe", 40);
        patient->ajouterAntecedent("Allergie au pomme");
        cardiologue.opererCoeur(patient);
        assert(cardiologue.getNbPatients() == 11, "Erreur: Le nombre de patients du cardiologue n'a pas été mis à jour.");
        assert(cardiologue.getPatient() == patient, "Erreur: Le patient n'a pas été correctement assigné au médecin.");
        assert(patient->getTypeSoins() == TypeSoins::PAS_BESOIN, "Erreur: Le type de soin du patient n'a pas été correctement mis à jour.");
        assert(patient->getAntecedentsMedicaux()[1] == "Examen ou traitement cardiaque effectué par Dr. Brown.", "Erreur: Les antédecedants du patient n'ont pas été correctement mis à jour.");
        });

    testSuite.require("Test des mutateurs setNbPatients et setNbConferences", 1.0, [&]() {
        Cardiologue cardiologue("Dr. Brown", 10, 5, 3);
        cardiologue.setNbPatients(20);
        cardiologue.setNbConferences(10);
        assert(cardiologue.getNbPatients() == 20, "Erreur: Le nombre de patients n'a pas été mis à jour.");
        assert(cardiologue.getNbConferences() == 10, "Erreur: Le nombre de conférences n'a pas été mis à jour.");
        });

    testSuite.require("Ajout de publications", 1.0, [&]() {
        Cardiologue cardiologue("Dr. Brown", 15, 7, 4);
        cardiologue.ajouterPublications(5);
        assert(cardiologue.getNbPublications() == 5, "Erreur: Le nombre de publications n'a pas été correctement mis à jour.");
        });

    // Test 23: Test d'égalité entre deux cardiologues
    testSuite.require("Test d'égalité entre deux cardiologues", 1.0, [&]() {
        Cardiologue cardiologue1("Dr. Brown", 15, 7, 4);
        Cardiologue cardiologue2("Dr. Brown", 15, 7, 4);
        assert(cardiologue1 == cardiologue2, "Erreur: Deux cardiologues identiques ne sont pas égaux.");

        Cardiologue cardiologue3("Dr. Green", 10, 5, 3);
        assert(!(cardiologue1 == cardiologue3), "Erreur: Deux cardiologues différents sont égaux.");
        });


    //****************************Test Infirmier**********************************/

    testSuite.require("Test du constructeur par défaut et des accesseurs", 1.0, [&]() {
        Infirmier infirmier("Dupont", "Jean", 25.0);
        assert(infirmier.getNom() == "Dupont", "Erreur: Le nom de l'infirmier n'est pas correct.");
        assert(infirmier.getPrenom() == "Jean", "Erreur: Le prénom de l'infirmier n'est pas correct.");
        assert(infirmier.getTauxHoraire() == 25.0, "Erreur: Le taux horaire de l'infirmier n'est pas correct.");
        assert(infirmier.getHeuresTravaillees() == 0, "Erreur: Les heures travaillées devraient être initialisées à 0.");
        });

    testSuite.require("Test du constructeur de copie", 1.0, [&]() {
        Infirmier infirmier1("Dupont", "Jean", 25.0);
        Infirmier infirmier2 = infirmier1;
        assert(infirmier2.getNom() == "Dupont", "Erreur: Le nom de l'infirmier copié n'est pas correct.");
        assert(infirmier2.getPrenom() == "Jean", "Erreur: Le prénom de l'infirmier copié n'est pas correct.");
        assert(infirmier2.getTauxHoraire() == 25.0, "Erreur: Le taux horaire de l'infirmier copié n'est pas correct.");
        assert(infirmier2.getHeuresTravaillees() == 0, "Erreur: Les heures travaillées de l'infirmier copié devraient être 0.");
        });

    testSuite.require("Test de la surcharge de l'opérateur += (ajout de chambres)", 1.0, [&]() {
        Infirmier infirmier("Dupont", "Jean", 25.0);
        infirmier += 101;
        infirmier += 102;
        assert(infirmier.getListeChambre().size() == 2, "Erreur: Le nombre de chambres ne correspond pas.");
        assert(infirmier.getListeChambre()[0] == "101", "Erreur: La première chambre n'est pas correcte.");
        assert(infirmier.getListeChambre()[1] == "102", "Erreur: La deuxième chambre n'est pas correcte.");
        });

    testSuite.require("Test de l'ajout des heures travaillées", 1.0, [&]() {
        Infirmier infirmier("Dupont", "Jean", 25.0);
        infirmier.ajouterHeuresTravaillees(10);
        assert(infirmier.getHeuresTravaillees() == 10, "Erreur: Le nombre d'heures travaillées n'est pas correct.");
        });

    testSuite.require("Test du calcul du salaire", 1.0, [&]() {
        Infirmier infirmier("Dupont", "Jean", 25.0);
        infirmier.ajouterHeuresTravaillees(10);
        infirmier += 101;
        float salaire = infirmier.calculerSalaire();
        float salaireAttendu = 251.25;
        assert(salaire == salaireAttendu, "Erreur: Le calcul du salaire est incorrect.");
        });

    testSuite.require("Test de l'examen d'un patient", 1.0, [&]() {
        Infirmier infirmier("Dupont", "Jean", 25.0);
        shared_ptr<Patient> patient = make_shared<Patient>("John Doe", 40);
        patient->misAjourSalle(10);
        infirmier.examinerPatient(patient);
        assert(infirmier.getPatient() == patient, "Erreur: Le patient n'a pas été correctement assigné à l'infirmier.");
        assert(infirmier.getHeuresTravaillees() == 5, "Erreur: Le nombre d'heures travaillées après l'examen n'est pas correct.");
        assert(patient->getTypeSoins() == TypeSoins::CHIRURGICAL, "Erreur: Le type de soin du patient n'a pas été mis à jour correctement.");
        assert(infirmier.getListeChambre().size() == 1, "Liste des chambre non mis à jour.");

        shared_ptr<Patient> patient2 = make_shared<Patient>("John Doe", 40);
        patient2->misAjourSalle(11);
        infirmier.examinerPatient(patient2);
        assert(patient2->getTypeSoins() == TypeSoins::CARDIOLOGIE, "Erreur: Le type de soin du patient n'a pas été mis à jour correctement.");
        assert(infirmier.getListeChambre().size() == 2, "Liste des chambre non mis à jour.");


        shared_ptr<Patient> patient3 = make_shared<Patient>("John Doe", 40);
        patient3->misAjourSalle(12);
        infirmier.examinerPatient(patient3);
        assert(patient3->getTypeSoins() == TypeSoins::PEDIATRIE, "Erreur: Le type de soin du patient n'a pas été mis à jour correctement.");
        assert(infirmier.getListeChambre().size() == 3, "Liste des chambre non mis à jour.");


        shared_ptr<Patient> patient4 = make_shared<Patient>("John Doe", 40);
        patient4->misAjourSalle(13);
        infirmier.examinerPatient(patient4);
        assert(patient4->getTypeSoins() == TypeSoins::CHIRURGICAL, "Erreur: Le type de soin du patient n'a pas été mis à jour correctement.");
        assert(infirmier.getListeChambre().size() == 4, "Liste des chambre non mis à jour.");

        });

    testSuite.require("Test de la surcharge de l'opérateur == (comparaison d'infirmiers)", 1.0, [&]() {
        Infirmier infirmier1("Dupont", "Jean", 25.0);
        Infirmier infirmier2("Dupont", "Jean", 25.0);
        Infirmier infirmier3("Durand", "Paul", 30.0);
        assert(infirmier1 == infirmier2, "Erreur: Les infirmiers identiques ne sont pas égaux.");
        assert(!(infirmier1 == infirmier3), "Erreur: Les infirmiers différents sont égaux.");
        });

    testSuite.require("Test de l'affichage d'un infirmier", 1.0, [&]() {
        Infirmier infirmier("Dupont", "Jean", 25.0);

        shared_ptr<Patient> patient1 = make_shared<Patient>("John Doe", 40);
        patient1->misAjourSalle(10);

        shared_ptr<Patient> patient2 = make_shared<Patient>("John Doe", 40);
        patient2->misAjourSalle(11);

        shared_ptr<Patient> patient3 = make_shared<Patient>("John Doe", 40);
        patient3->misAjourSalle(12);

        shared_ptr<Patient> patient4 = make_shared<Patient>("John Doe", 40);
        patient4->misAjourSalle(13);

        infirmier.examinerPatient(patient1);
        infirmier.examinerPatient(patient2);
        infirmier.examinerPatient(patient3);
        infirmier.examinerPatient(patient4);

        ostringstream oss;
        streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
        oss << infirmier;
        cout.rdbuf(oldCout);

        string output = oss.str();
        string expectedOutput =
            "Nom: Dupont\n"
            "Prenom: Jean\n"
            "Taux horaire: 25 $/h\n"
            "Heures travaillees: 20 heures\n"
            "Liste des chambres: 10 11 12 13 \n";
        assert(output == expectedOutput, "Erreur: Le format de l'affichage de l'infirmier est incorrect.");
        });


    //***************************Test HopitalPoly***********************/

    testSuite.require("Constructeur et accesseurs", 1.0, [&]() {
        HopitalPoly hopital("Hôpital Général");
        assert(hopital.getNom() == "Hôpital Général", "Erreur: Le nom de l'hôpital n'a pas été initialisé correctement.");
        assert(hopital.getEmployes().size() == 0, "Erreur: La liste des employés devrait être vide à l'initialisation.");
        });

    testSuite.require("Ajout d'un employé", 1.0, [&]() {
        HopitalPoly hopital("Hôpital Général");
        shared_ptr<Infirmier> infirmier = make_shared<Infirmier>("Jane", "Doe", 25.0f);

        hopital += infirmier;
        assert(hopital.getEmployes().size() == 1, "Erreur: L'employé n'a pas été ajouté correctement.");

        // Ajout du même employé en double
        hopital += infirmier;
        assert(hopital.getEmployes().size() == 1, "Erreur: L'employé en double a été ajouté.");
        });

    testSuite.require("Fusion de deux hôpitaux", 1.0, [&]() {
        HopitalPoly hopital1("Hôpital Général");
        HopitalPoly hopital2("Hôpital Régional");

        shared_ptr<Infirmier> infirmier = make_shared<Infirmier>("Jane", "Doe", 25.0f);
        shared_ptr<Medecin> medecin = make_shared<Cardiologue>("Dr. Smith", 10, 5);

        hopital1 += infirmier;
        hopital2 += medecin;

        hopital1 += hopital2; // Fusion des deux hôpitaux
        assert(hopital1.getEmployes().size() == 2, "Erreur: La fusion des hôpitaux n'a pas fonctionné correctement.");

        // Fusion avec un hôpital vide
        HopitalPoly hopitalVide("Hôpital Vide");
        hopital1 += hopitalVide;
        assert(hopital1.getEmployes().size() == 2, "Erreur: La fusion avec un hôpital vide a modifié la liste des employés.");
        });

    testSuite.require("Suppression d'un employé", 1.0, [&]() {
        HopitalPoly hopital("Hôpital Général");
        shared_ptr<Infirmier> infirmier = make_shared<Infirmier>("Jane", "Doe", 25.0f);

        hopital += infirmier;
        hopital -= infirmier; // Suppression de l'employé
        assert(hopital.getEmployes().size() == 0, "Erreur: L'employé n'a pas été supprimé correctement.");

        // Suppression d'un employé inexistant
        hopital -= infirmier;
        assert(hopital.getEmployes().size() == 0, "Erreur: La suppression d'un employé inexistant a modifié la liste.");
        });

    testSuite.require("Suppression d'un employé par son nom", 1.0, [&]() {
        HopitalPoly hopital("Hôpital Général");
        shared_ptr<Infirmier> infirmier = make_shared<Infirmier>("Jane", "Doe", 25.0f);

        hopital += infirmier;
        hopital -= "Jane"; // Suppression par nom
        assert(hopital.getEmployes().size() == 0, "Erreur: L'employé n'a pas été supprimé correctement par son nom.");

        // Suppression avec un nom inexistant
        hopital += infirmier;
        hopital -= "Inconnu";
        assert(hopital.getEmployes().size() == 1, "Erreur: La suppression avec un nom inexistant a modifié la liste.");
        });

    testSuite.require("Recherche d'un employé disponible", 1.0, [&]() {
        HopitalPoly hopital("Hôpital Général");
        shared_ptr<Infirmier> infirmier = make_shared<Infirmier>("Jane", "Doe", 25.0f);
        shared_ptr<Cardiologue> cardiologue = make_shared<Cardiologue>("Dr. Smith", 10, 5);
        shared_ptr<Pediatre> pediatre = make_shared<Pediatre>("Dr. William", 10, 5);
        pediatre->setPatient(make_shared<Patient>("Bertrand", 15));

        hopital += infirmier;
        hopital += cardiologue;
        hopital += pediatre;

        auto employeTrouve = hopital.trouverEmployeLibre<Cardiologue>();
        assert(employeTrouve == cardiologue, "Erreur: Aucun cardiologue disponible n'a été trouvé.");

        auto employeTrouve2 = hopital.trouverEmployeLibre<Pediatre>();
        assert(employeTrouve2 == nullptr, "Erreur: Aucun pediatre ne devrait être trouvé car tous occupé.");

        auto employeInexistant = hopital.trouverEmployeLibre<Chirurgien>();
        assert(employeInexistant == nullptr, "Erreur: Un chirurgien a été trouvé alors qu'il n'existe pas.");
        });

    testSuite.require("Calcul du coût salarial total", 1.0, [&]() {
        HopitalPoly hopital("Hôpital Général");
        shared_ptr<Infirmier> infirmier = make_shared<Infirmier>("Jane", "Doe", 25.0f);
        shared_ptr<Cardiologue> cardiologue = make_shared<Cardiologue>("Dr. Smith", 10, 5);

        hopital += infirmier;
        hopital += cardiologue;

        float coutTotal = hopital.coutSalarialTotal();
        float coutAttendu = infirmier->calculerSalaire() + cardiologue->calculerSalaire();
        assert(coutTotal == coutAttendu, "Erreur: Le coût salarial total est incorrect.");

        // Coût salarial d'un hôpital sans employés
        HopitalPoly hopitalVide("Hôpital Vide");
        assert(hopitalVide.coutSalarialTotal() == 0.0f, "Erreur: Le coût salarial d'un hôpital vide devrait être 0.");
        });

    testSuite.require("Accueil d'un patient", 1.0, [&]() {
        HopitalPoly hopital("Hôpital Général");
        shared_ptr<Infirmier> infirmier = make_shared<Infirmier>("Jane", "Doe", 25.0f);
        shared_ptr<Patient> patient = make_shared<Patient>("John Doe", 30);

        hopital += infirmier;
        hopital.accueillirPatient(patient);

        assert(patient->getSalle() == 0, "Erreur: Salle incorrecte assignée au patient.");
        assert(infirmier->getPatient() == patient, "Erreur: Le patient n'a pas été correctement assigné à l'infirmier.");
        assert(patient->getInfirmier() == infirmier, "Erreur: L'infirmier n'a pas été assigné au patient.");
        assert(infirmier->getListeChambre().size() == 1, "Liste des chambres de l'infirmiere non mis à jour");
        assert(hopital.getPatients().size() == 1, "Liste des patients non mis à jour");

        shared_ptr<Patient> patient2 = make_shared<Patient>("Jane Doe", 25);
        hopital.accueillirPatient(patient2);

        assert(patient2->getSalle() == 1, "Salle incorrecte assignée au patient.");
        assert(patient2->getInfirmier() == nullptr, "Erreur: L'infirmier n'a pas été assigné au patient.");
        assert(infirmier->getListeChambre().size() == 1, "Liste des chambres de l'infirmiere non mis à jour");
        assert(hopital.getPatients().size() == 2, "Liste des patients non mis à jour");

        shared_ptr<Infirmier> infirmier2 = make_shared<Infirmier>("Johnny", "Doe", 25.0f);
        hopital += infirmier2;
        hopital.accueillirPatient(patient2);

        assert(patient2->getSalle() == 1, "Erreur: Le patient n'a pas été assigné à un infirmier.");
        assert(infirmier2->getPatient() == patient2, "Erreur: Le patient n'a pas été assigné à un infirmier.");
        assert(patient2->getInfirmier() == infirmier2, "Erreur: L'infirmier n'a pas été correctement assigné au patient.");
        assert(infirmier2->getListeChambre().size() == 1, "Liste des chambres de l'infirmiere non mis à jour");
        assert(hopital.getPatients().size() == 2, "Liste des patients non mis à jour");

        });

    testSuite.require("Traitement des patients", 1.0, [&]() {
        HopitalPoly hopital("Hôpital Général");
        shared_ptr<Infirmier> infirmier = make_shared<Infirmier>("Jane", "Doe", 25.0f);
        shared_ptr<Cardiologue> cardiologue = make_shared<Cardiologue>("Dr. Smith", 10, 5);
        shared_ptr<Patient> patient = make_shared<Patient>("John Doe", 30);
        shared_ptr<Patient> patient2 = make_shared<Patient>("Johnny Doe", 30);
        shared_ptr<Patient> patient3 = make_shared<Patient>("Jann Doe", 30);

        hopital += infirmier;
        hopital += cardiologue;
        hopital.accueillirPatient(patient);
        hopital.accueillirPatient(patient2);
        hopital.accueillirPatient(patient3);

        assert(hopital.getPatients().size() == 3, "Erreur: Taille liste des patients incorrectes.");

        patient->misAjourTypeSoin(TypeSoins::CARDIOLOGIE);
        patient2->misAjourTypeSoin(TypeSoins::CHIRURGICAL);
        patient3->misAjourTypeSoin(TypeSoins::PEDIATRIE);

        hopital.traiterPatients();

        assert(patient->getMedecin() == cardiologue, "Erreur: Le patient n'a pas été correctement traité.");
        assert(hopital.getPatients().size() == 2, "Erreur: Taille liste des patients incorrectes.");

        // Traiter un patient sans médecin disponible
        HopitalPoly hopitalSansMedecin("Hôpital Sans Médecin");
        shared_ptr<Patient> patient4 = make_shared<Patient>("Jane Doe", 25);

        hopitalSansMedecin.accueillirPatient(patient4);
        patient2->misAjourTypeSoin(TypeSoins::CHIRURGICAL);
        hopitalSansMedecin.traiterPatients();

        assert(patient2->getMedecin() == nullptr, "Erreur: Un patient a été traité sans médecin disponible.");
        });

    testSuite.require("Recherche d'un employé", 1.0, [&]() {
        HopitalPoly hopital("Hôpital Général");
        shared_ptr<Infirmier> infirmier = make_shared<Infirmier>("Jane", "Doe", 25.0f);

        hopital += infirmier;

        assert(hopital.chercherEmploye(infirmier), "Erreur: L'employé n'a pas été trouvé par objet.");
        assert(hopital.chercherEmploye("Jane"), "Erreur: L'employé n'a pas été trouvé par nom.");

        // Recherche d'un employé inexistant
        shared_ptr<Infirmier> infirmierInexistant = make_shared<Infirmier>("Inconnu", "Inconnu", 0.0f);
        assert(!hopital.chercherEmploye(infirmierInexistant), "Erreur: Un employé inexistant a été trouvé.");
        assert(!hopital.chercherEmploye("Inconnu"), "Erreur: Un employé inexistant a été trouvé par nom.");
        });

    testSuite.require("Affichage des employés et de l'hôpital", 1.0, [&]() {
        HopitalPoly hopital("Hôpital Général");
        shared_ptr<Infirmier> infirmier = make_shared<Infirmier>("Jane", "Doe", 25.0f);

        hopital += infirmier;

        ostringstream oss;
        streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
        oss << hopital;
        cout.rdbuf(oldCout);

        string output = oss.str();
        string expectedOutput =
            "Hôpital: Hôpital Général\n"
            "Employés: \n"
            "Nom: Jane\n"
            "Prenom: Doe\n"
            "Taux horaire: 25 $/h\n"
            "Heures travaillees: 0 heures\n"
            "Liste des chambres: Aucune chambre assignee.\n\n";

        assert(output == expectedOutput, "Erreur: L'affichage de l'hôpital est incorrect.");

        // Affichage d'un hôpital sans employés
        HopitalPoly hopitalVide("Hôpital Vide");
        ostringstream ossVide;
        streambuf* oldCoutVide = std::cout.rdbuf(ossVide.rdbuf());
        ossVide << hopitalVide;
        cout.rdbuf(oldCoutVide);

        string outputVide = ossVide.str();
        string expectedOutputVide =
            "Hôpital: Hôpital Vide\n"
            "Employés: \n";
        assert(outputVide == expectedOutputVide, "Erreur: L'affichage d'un hôpital sans employés est incorrect.");
        });

    // Affichage des résultats des tests
    testSuite.showResults();

    return 0;
}