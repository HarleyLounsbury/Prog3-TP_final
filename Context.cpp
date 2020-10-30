// Context.cpp
// Définition de class "Context"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

#include "Biblio.h"

// ###################################################
// encranBienvenue()
// Afficher l'en-tête du programme.
// ###################################################
void Context::ecranBienvenue()
{
   char coinHG = (char)201;
   char coinHD = (char)187;
   char coinBG = (char)200;
   char coinBD = (char)188;
   char ligneH = (char)205;
   char ligneV = (char)186;

   system("cls");
   setlocale(LC_ALL, "C");
   cout << "\t" << coinHG;
   for (int i = 0; i < 48; i++)
      cout << ligneH;
   cout << coinHD << endl;
   cout << "\t" << ligneV << "                                                " << ligneV << endl;
   cout << "\t" << ligneV << "  Harley Lounsbury pr\x82sente :                   " << ligneV << endl;
   cout << "\t" << ligneV << "           Regard Sant\x82                         " << ligneV << endl;
   cout << "\t" << ligneV << "  Syst\x8Ame de consultation de dossiers sant\x82     " << ligneV << endl;
   cout << "\t" << ligneV << "                                                " << ligneV << endl;
   cout << "\t" << coinBG;
   for (int i = 0; i < 48; i++)
      cout << ligneH;
   cout << coinBD << endl;
   setlocale(LC_ALL, "");

   return;
}

// ###################################################
// menuPrincipale()
// Afficher le menu principal.
// ###################################################
char Context::menuPrincipal()
{
   string Choix;
   ecranBienvenue();
   cout << "\nProfils offerts:\n\n";

   cout << "\tC-Citoyen\n";
   cout << "\tP-Professionnel de la santé\n\n";
   cout << "\tQ-Quitter\n";

   cout << "\t\tVotre choix:";
   getline(cin, Choix);
   if (Choix.length() == 1)
      return toupper(Choix[0]);
   else
      return '\n';
}

// ###################################################
// traiterCitoyen()
// Traitement de dossiers de citoyens.
// ###################################################
void Context::traiterCitoyen()
{
   string strNAS;

   while (true)
   {
      ecranBienvenue();
      cout << "\nProfil citoyen\n";
      cout << "\n\tNuméro d'assurance sociale du citoyen\n\t(Q pour quitter)\n";
      cout << "\tNAS:";
      getline(cin, strNAS);

      if (toupper(strNAS[0]) == ('Q'))
         return;
    
      if (!Indexeur.estIndexeCitoyen(strNAS))
      {
         chercherCitoyenNonIndexe(strNAS);
         return;
      }     
      chercherCitoyenIndexe(strNAS);
      return;
   }
   
   return;
}

// ###################################################
// chercherCitoyenNonIndexe()
// méchanism pour trouver le citoyen non-indexé
// ###################################################
void Context::chercherCitoyenNonIndexe(string NAS)
{
   ifstream fichierPopIn(FICHIER_POPULATION);
   string ligneCourante;
   Parseur<Citoyen> ParCit(";");
   int nbValeurs;
   vector<string> valeurs;
   int positionTotale = 0;

   NAS += ";";

   while (fichierPopIn.good())
   {
      getline(fichierPopIn, ligneCourante);
      if (ligneCourante.find(NAS) == 0)
      {
         nbValeurs = ParCit.CompteurChamp(ligneCourante) + 1;
         ParCit.Decouper(ligneCourante, valeurs, nbValeurs);
         fichierPopIn.close();
         Indexeur.IndexerCitoyen(NAS.substr(0, NAS.length() - 1), positionTotale);
         Citoyen citCourant(valeurs, false);
         vueCitoyen(citCourant);
         return;
      }
      positionTotale += ligneCourante.length();
      positionTotale += 2;    // 2 caractères dans un \n
   }
   fichierPopIn.close();

   cout << "NAS pas trouvé." << endl;
   system("pause");

   return;
}

// ###################################################
// chercherCitoyenIndexe()
// méchanism pour trouver le citoyen indexé
// ###################################################
void Context::chercherCitoyenIndexe(string NAS)
{
   ifstream fichierIndexIn(FICHIER_INDEX_CITOYENS);
   string ligne;
   Parseur<Citoyen> ParCit(";");
   int nbValeurs;
   vector<string> valeurs;
   int position = Indexeur.retournerIndexCitoyen(NAS);

   ifstream fichierPopIn(FICHIER_POPULATION);
   fichierPopIn.seekg(position);
   getline(fichierPopIn, ligne);
   nbValeurs = ParCit.CompteurChamp(ligne) + 1;
   ParCit.Decouper(ligne, valeurs, nbValeurs);
   fichierPopIn.close();
   Citoyen citCourant(valeurs, true);
   vueCitoyen(citCourant);

   return;
}

// ###################################################
// vueCitoyen()
// Afficher le sommaire, demander à l'utilisateur pour voir plus de détails.
// ###################################################
void Context::vueCitoyen(Citoyen &cit)
{
   ecranBienvenue();
   afficherSommaireCitoyen(cit);
   char Choix = menuCitoyen();
   while (Choix != 'Q')
   {
      switch (toupper(Choix))
      {
      case 'P':
         vueProbleme(cit); 
         break;
      case 'R': 
         vueRessource(cit); 
         break;
      }
      ecranBienvenue();
      afficherSommaireCitoyen(cit);
      Choix = menuCitoyen();
   }
   return;
}

// ###################################################
// afficherSommaireCitoyen()
// Afficher le sommaire du citoyen
// ###################################################
void Context::afficherSommaireCitoyen(Citoyen& cit)
{
   cout << "--------------------\n";
   cout << "Nom:\t\t" << cit.G_nom() << endl;
   cout << "Né(e) le:\t" << cit.G_naissance() << "\n";
   cout << "--------------------\n";
   cout << "Historique:\n\t" << cit.G_nbProblemes() << " problèmes\n\t" << cit.G_nbUtilisations() << " ressources utilisées\n\n";
   cout << "--------------------\n";

   return;
}

// ###################################################
// menuCitoyen()
// Afficher le menu du citoyen, saisir et retourner le choix
// ###################################################
char Context::menuCitoyen()
{
   string Choix;
   cout << "Consulter:" << endl;
   cout << "\t" << "P-problèmes\n";
   cout << "\t" << "R-ressources\n";
   cout << "\t" << "Q-Retour\n";
   cout << "\t" << "\t\tVotre choix:";
   getline(cin, Choix);
   if (Choix.length() == 1)
      return toupper(Choix[0]);
   else
      return '\n';
}

// ###################################################
// vueProbleme()
// Rediriger l'utilisateur vers son choix
// ###################################################
void Context::vueProbleme(Citoyen& cit)
{
   ecranBienvenue();
   
   char Choix = menuProbleme();
   while (Choix != 'Q')
   {
      switch (toupper(Choix))
      {
      case 'B':
         vueBlessure(cit);
         break;
      case 'M':
         vueMaladie(cit); 
         break;
      case 'T':
         vueProblemeTous(cit); 
         break;
      }
      ecranBienvenue();
      Choix = menuProbleme();
   }
   return;
}

// ###################################################
// menuProbleme()
// Afficher le menu du problèmes, saisir et retourner le choix
// ###################################################
char Context::menuProbleme()
{
   string Choix;
   cout << "Consulter:" << endl << endl;
   cout << "\t" << "B-Blessures\n";
   cout << "\t" << "M-Maladies\n";
   cout << "\t" << "T-Tous les problèmes\n";
   cout << "\t" << "Q-Retour\n";
   cout << "\t" << "\t\tVotre choix:";
   getline(cin, Choix);
   if (Choix.length() == 1)
      return toupper(Choix[0]);
   else
      return '\n';
}

// ###################################################
// vueBlessure()
// Afficher l'écran de blessures du citoyen
// ###################################################
void Context::vueBlessure(Citoyen& cit)
{
   ecranBienvenue();
   cout << "Blessures de " << cit.G_nom() << endl;
   cit.AfficherBlessures();

   system("pause");

   return;
}

// ###################################################
// vueMaladie()
// Afficher l'écran de maladies du citoyen
// ###################################################
void Context::vueMaladie(Citoyen& cit)
{
   ecranBienvenue();
   cout << "Maladies de " << cit.G_nom() << endl;
   cit.AfficherMaladies();

   system("pause");

   return;
}

// ###################################################
// vueProblemeTous()
// Afficher l'écran de problèmes du citoyen
// ###################################################
void Context::vueProblemeTous(Citoyen& cit)
{
   ecranBienvenue();

   cout << "Problèmes médicaux de " << cit.G_nom() << endl;
   cout << setw(62) << setfill('-') << "-" << setfill(' ') << endl;
   cout << "Blessures:" << endl;
   cit.AfficherBlessures();
   
   cout << endl << "Maladies:" << endl;
   cit.AfficherMaladies();
   cout << endl;

   system("pause");

   return;
}

// ###################################################
// vueRessource()
// Rediriger l'utilisateur vers son choix
// ###################################################
void Context::vueRessource(Citoyen& cit)
{
   enteteVueRessource(cit);
   char Choix = menuRessource();
   
   while (Choix != 'Q')
   {
      switch (toupper(Choix))
      {
      case 'R': 
         vueRendezvous(cit); 
         break;
      case 'H': 
         vueHospitalisation(cit); 
         break;
      case 'T': 
         vueRessourceToutes(cit); 
         break;
      }

      enteteVueRessource(cit);
      Choix = menuRessource();
   }

   return;
}

// ###################################################
// enteteVueRessource()
// Afficher en-tete des ressources
// ###################################################
void Context::enteteVueRessource(Citoyen& cit)
{
   ecranBienvenue();
   cout << "Ressources utilisées par " << cit.G_nom() << "\n-----------------------------------\n";
   cout << "\t" << cit.G_nbRendezvous() << " rendez-vous\n";
   cout << "\t" << cit.G_nbHospitalisations() << " hospitalisations\n";
   cout << "-----------------------------------\n";

   return;
}

// ###################################################
// menuRessource()
// Afficher menu de ressources, saisir et retourner le choix de l'utilisateur
// ###################################################
char Context::menuRessource()
{
   string Choix;
   cout << "Consulter:" << endl << endl;
   cout << "\t" << "R-Rendez-vous\n";
   cout << "\t" << "H-Hospitalisation\n";
   cout << "\t" << "T-Toutes les ressouces utilisées\n";
   cout << "\t" << "Q-Retour\n";
   cout << "\t" << "\t\tVotre choix:";
   getline(cin, Choix);
   if (Choix.length() == 1)
      return toupper(Choix[0]);
   else
      return '\n';
}

// ###################################################
// vueRendezvous()
// Afficher les rendez-vous du citoyen
// ###################################################
void Context::vueRendezvous(Citoyen& cit)
{
   ecranBienvenue();
   cout << "Rendez-vous de " << cit.G_nom() << endl;
   cit.AfficherRendezvous();
   cout << endl;

   system("pause");

   return;
}

// ###################################################
// vueHospitalisation()
// Afficher les hospitalisations du citoyen
// ###################################################
void Context::vueHospitalisation(Citoyen& cit)
{
   ecranBienvenue();
   cout << "Hospitalistions de " << cit.G_nom() << endl;
   cit.AfficherHospitalisations();
   cout << endl;

   system("pause");

   return;
}

// ###################################################
// vueRessourceToutes()
// Afficher les ressources du citoyen
// ###################################################
void Context::vueRessourceToutes(Citoyen& cit)
{
   ecranBienvenue();

   cout << "Ressources utilisées par " << cit.G_nom() << endl;
   cout << setw(62) << setfill('-') << "-" << setfill(' ') << endl;
   
   cout << "Rendez-vous simples: " << endl;
   cit.AfficherRendezvous();
   
   cout << endl << "Hospitalisations:" << endl;
   cit.AfficherHospitalisations();
   cout << endl;

   system("pause");

   return;
}

// ###################################################
// traiterProfessionnel()
// Traitement de dossiers de professionnels de la santé.
// ###################################################
void Context::traiterProfessionnel()
{
   string codePS;

   while (codePS[0] != 'Q')
   {
      ecranBienvenue();
      cout << "\nProfil professionnel de la santé\n";
      cout << "\n\tCode du professionnel désiré\n\t(Q pour quitter)\n";
      cout << "\tCode PS:";
      
      getline(cin, codePS);

      if (toupper(codePS[0]) == ('Q'))
         break;

      if (!validerCodePS(codePS))
      {
         cout << "Code PS non-valide. Appuyer sur une touche pour continuer ou Q pour retourner au menu principale.\n";
         getline(cin, codePS);
         if (toupper(codePS[0]) == ('Q'))
            return;
         traiterProfessionnel();
         return;
      }

      if (!Indexeur.estIndexeProfessionnel(codePS))
      {
         chercherProfessionnelNonIndexe(codePS);
         break;
      }
      chercherProfessionnelIndexe(codePS);
   }
   system("pause");
   return;
}

// ###################################################
// validerCodePS()
// Valider le code PS selon le critères connus
// ###################################################
bool Context::validerCodePS(string codePS)
{ 
   
   for (int i = 0; i < CODES_PS.size(); i++)
   {
      if (codePS.find(CODES_PS[i]) == 0)
         break;
      
      if (i == CODES_PS.size() - 1)
         return false;
   }

   if (codePS.length() < CODE_PS_MIN)
      return false;

   if (codePS.length() > CODE_PS_MAX)
      return false;

   // Autres conditions de validations pourrait s'ajouter pour une validation plus compréhensive.
   return true;
}

// ###################################################
// chercherProfessionnelNonIndexe()
// Méchanism de chercher le professionel non-indexé
// ###################################################
void Context::chercherProfessionnelNonIndexe(string codePS)
{
   ifstream fichierPopIn(FICHIER_POPULATION);
   string ligneCourante;
   int positionTotale = 0;

   codePS += ";";

   while (fichierPopIn.good())
   {
      getline(fichierPopIn, ligneCourante);
      if (ligneCourante.find(codePS) != -1)
      {
         fichierPopIn.close();
         Parseur<ProfessionnelSante> ParPro(";");
         vector<string> valeurs;
         int nbValeurs = ParPro.CompteurChamp(ligneCourante) + 1;
         ParPro.Decouper(ligneCourante, valeurs, nbValeurs);
         if (nbValeurs != 5 || valeurs[0] == "")
            break;
         ProfessionnelSante proCourant(valeurs, false);
         vueProfessionnel(proCourant);
         Indexeur.IndexerProfessionnel(codePS, positionTotale);
         return;
      }
      positionTotale += ligneCourante.length();
      positionTotale += 2; // pour le \n à la fin de chaque ligne. 
   }

   fichierPopIn.close();

   cout << "Code PS pas trouvé." << endl;
   return;
}

// ###################################################
// chercherProfessionnelIndexe()
// Méchanism de chercher le professionel indexé
// ###################################################
void Context::chercherProfessionnelIndexe(string codePS)
{
   ifstream fichierIndexIn(FICHIER_INDEX_PROFESSIONNELS);
   string ligne;
   Parseur<ProfessionnelSante> ParCit(";");
   int nbValeurs;
   vector<string> valeurs;
   int position = Indexeur.retournerIndexProfessionnel(codePS);

   ifstream fichierPopIn(FICHIER_POPULATION);
   fichierPopIn.seekg(position);
   getline(fichierPopIn, ligne);
   nbValeurs = ParCit.CompteurChamp(ligne) + 1;
   ParCit.Decouper(ligne, valeurs, nbValeurs);
   fichierPopIn.close();
   ProfessionnelSante proCourant(valeurs, true);
   vueProfessionnel(proCourant);

   return;
}

// ###################################################
// vueProfessionnel()
// Afficher le sommaire de professionnel
// ###################################################
void Context::vueProfessionnel(ProfessionnelSante& pro)
{
   string strCode;
   char Choix;

   ecranBienvenue();
   enTeteProfessionnel(pro);
   Choix = menuProfessionnel();

   while (Choix != 'Q')
   {
      switch (toupper(Choix))
      {
      case 'P': 
         vuePatient(pro);
         break;
      case 'I': 
         vueIntervention(pro); 
         break;
      }

      ecranBienvenue();
      enTeteProfessionnel(pro);
      Choix = menuProfessionnel();
   }
   return;
}

// ###################################################
// enTeteProfessionnel()
// Afficher l'en-tête de professionnel
// ###################################################
void Context::enTeteProfessionnel(ProfessionnelSante& pro)
{
   cout << "--------------------\n";
   cout << "Nom:\t\t" << pro.G_nom() << ", " << pro.G_titre() << endl;
   cout << "Né(e) le:\t" << pro.G_naissance() << endl;
   cout << "--------------------\n";
   cout << "Historique:\n\t" << pro.G_lstPatients()->size() << " patients \n\t" << pro.G_lstInterventions()->size() << " interventions\n\n";
   cout << "--------------------\n";

   return;
}

// ###################################################
// menuProfessionnel()
// Afficher le menu de professionnel
// ###################################################
char Context::menuProfessionnel()
{
   string Choix;
   cout << "Consulter:" << endl << endl;
   cout << "\t" << "P-patients\n";
   cout << "\t" << "I-interventions\n";
   cout << "\t" << "Q-Retour\n";
   cout << "\t" << "\t\tVotre choix:";
   getline(cin, Choix);
   if (Choix.length() == 1)
      return toupper(Choix[0]);
   else
      return '\n';
}

// ###################################################
// vuePatient()
// Rediriger l'utilisateur vers son choix
// ###################################################
void Context::vuePatient(ProfessionnelSante& pro)
{
   ecranBienvenue();
   cout << "\tPatients de " << pro.G_nom() << " triés par:\n\n";
   char Choix = menuPatient();
   while (Choix != 'Q' && Choix != 'q')
   {
      switch (Choix)
      {
      case 's': 
         vuePatientBrut(pro); 
         break;
      case 'n': 
         vuePatientNaissance(pro);
         break;
      case 'N': 
         vuePatientNaissanceDec(pro);
         break;
      case 'a':
         vuePatientNAS(pro);
         break;
      case 'A': 
         vuePatientNASDec(pro);
         break;
      case 'o': 
         vuePatientNom(pro);
         break;
      case 'O': 
         vuePatientNomDec(pro); 
         break;
      }

      ecranBienvenue();
      cout << "\tPatients de " << pro.G_nom() << " triés par:\n\n";
      Choix = menuPatient();
   }

   return;
}

// ###################################################
// menuPatient()
// Menu d'options d'affichage de patients
// ###################################################
char Context::menuPatient()
{
   string Choix;

   cout << "\tn-naissance .:\n";
   cout << "\tN-Naissance :.\n";
   cout << "\ta-NAS .:\n";
   cout << "\tA-NAS :.\n";
   cout << "\to-Nom .:\n";
   cout << "\tO-Nom :.\n";
   cout << "\ts-sans tri\n";
   cout << "\tQ-Retour\n";
   cout << "\t\tVotre choix:";
   getline(cin, Choix);
   if (Choix.length() == 1)
      return Choix[0];
   else
      return '\n';
}

// ###################################################
// enTeteListePatient()
// Afficher l'en-tête pour la liste de patients
// ###################################################
void Context::enTeteListePatient(string nom)
{
   ecranBienvenue();
   cout << "Patients de " << nom << "\n-------------------------------------\n";
   cout << left << setw(30) << "NOM" << setw(8) << "NAS" << setw(16) << "Naissance" << "Nombre d'interventions\n";
   cout << "____________________________________________________________\n";

   return;
}

// ###################################################
// afficherListePatient()
// Afficher les informations pertinents de chaque patient
// ###################################################
void Context::afficherListePatient(ProfessionnelSante& pro)
{
   list<Citoyen*>::iterator iter = pro.G_lstPatients()->begin();
   list<Citoyen*>::iterator iterFin = pro.G_lstPatients()->end();
   cout << left;

   enTeteListePatient(pro.G_nom());
   for (iter; iter != iterFin; iter++)
      cout << setw(30) << (*iter)->G_nom() << setw(8) << (*iter)->G_NAS() << setw(16) << (*iter)->G_naissance() << pro.CompteInterventionsPourPatient((*iter)->G_NAS()) << endl;
   
   return;
}

// ###################################################
// vuePatientBrut()
// Afficher la liste de patients
// ###################################################
void Context::vuePatientBrut(ProfessionnelSante& pro)
{
   afficherListePatient(pro);
   system("pause");

   return;
}

// ###################################################
// vuePatientNaissance()
// Trier et afficher la liste de patients par date de naissance, croissante
// ###################################################
void Context::vuePatientNaissance(ProfessionnelSante& pro)
{
   Trieur t;
   t.parNaissanceAsc(*pro.G_lstPatients());
   afficherListePatient(pro);
   system("pause");

   return;
}

// ###################################################
// vuePatientNaissanceDec()
// Trier et afficher la liste de patients par date de naissance, décroissante
// ###################################################
void Context::vuePatientNaissanceDec(ProfessionnelSante& pro)
{
   Trieur t;
   t.parNaissanceDesc(*pro.G_lstPatients());
   afficherListePatient(pro);
   system("pause");

   return;
}

// ###################################################
// vuePatientNAS()
// Trier la liste de patient par NAS, croissante
// ###################################################
void Context::vuePatientNAS(ProfessionnelSante& pro)
{
   Trieur t;
   t.parNASAsc(*pro.G_lstPatients());
   afficherListePatient(pro);
   system("pause");

   return;
}

// ###################################################
// vuePatientNASDec()
// Trier la liste de patient par NAS, décroissante
// ###################################################
void Context::vuePatientNASDec(ProfessionnelSante& pro)
{
   Trieur t;
   t.parNASDesc(*pro.G_lstPatients());
   afficherListePatient(pro);
   system("pause");

   return;
}

// ###################################################
// vuePatientNom()
// Trier la liste de patient par nom, croissante
// ###################################################
void Context::vuePatientNom(ProfessionnelSante& pro)
{
   Trieur t;
   t.parNomAsc(*pro.G_lstPatients());
   afficherListePatient(pro);
   system("pause");

   return;
}

// ###################################################
// vuePatientNomDec()
// Trier la liste de patient par nom, décroissante
// ###################################################
void Context::vuePatientNomDec(ProfessionnelSante& pro)
{
   Trieur t;
   t.parNomDesc(*pro.G_lstPatients());
   enTeteListePatient(pro.G_nom());
   afficherListePatient(pro);
   system("pause");

   return;
}

// ###################################################
// vueIntervention()
// Rediriger l'utilisateur vers son choix
// ###################################################
void Context::vueIntervention(ProfessionnelSante& pro)
{
   ecranBienvenue();

   char Choix = menuIntervention();
   while (Choix != 'q' && Choix != 'Q')
   {
      switch (Choix)
      {
      case 'd': 
         vueInterventionDate(pro);
         break;
      case 'D':
         vueInterventionDateDesc(pro);
         break;
      case 'e':
         vueInterventionEtablissement(pro);
         break;
      case 'E': 
         vueInterventionEtablissementDesc(pro);
         break;
      case 's': 
         vueInterventionBrut(pro);
         break;
      }
      ecranBienvenue();
      Choix = menuIntervention();
   }

   return;
}

// ###################################################
// menuIntervention()
// Afficher le menu des interventions, saisir et retourner le choix de l'utilisateur
// ###################################################
char Context::menuIntervention()
{
   string Choix;
   cout << "\tInterventions de Louise Décarie triées par:\n\n";
   cout << "\td-date .:\n";
   cout << "\tD-date :.\n";
   cout << "\te-établissement .:\n";
   cout << "\tE-établissement :.\n";
   cout << "\ts-sans tri\n";
   cout << "\tQ-Retour\n";
   cout << "\t\tVotre choix:";
   getline(cin, Choix);
   if (Choix.length() == 1)
      return Choix[0];
   else
      return '\n';
}

// ###################################################
// menuIntervention()
// Afficher l'en-tête des interventions
// ###################################################
void Context::enTeteListeInterventions(string nom)
{
   ecranBienvenue();
   cout << left;
   cout << "Interventions de " << nom << "\n-------------------------------------\n";
   cout << setw(29) << "Patient" << setw(6) << "NAS" << setw(13) << "Date" << "Établissement\n";   
   cout << setw(72) << setfill('_') << "_" << "\n";
   cout << setfill(' ');

   return;
}

// ###################################################
// afficherListeInterventions()
// Afficher la liste des interventions
// ###################################################
void Context::afficherListeInterventions(ProfessionnelSante& pro)
{
   list<Utilisation*>::iterator iterUtil = pro.G_lstInterventions()->begin();
   list<Utilisation*>::iterator iterUtilFin = pro.G_lstInterventions()->end();
   list<Citoyen*>::iterator iterCit;
   list<Citoyen*>::iterator iterCitFin = pro.G_lstPatients()->end();
   cout << left;
   enTeteListeInterventions(pro.G_nom());

   for (iterUtil; iterUtil != iterUtilFin; iterUtil++)
   {
      iterCit = pro.G_lstPatients()->begin();
      for (iterCit; iterCit != iterCitFin; iterCit++)
      {
         if ((*iterUtil)->G_NAS() == (*iterCit)->G_NAS())
         {
            cout << setw(29) << (*iterCit)->G_nom() << setw(6) << (*iterCit)->G_NAS() << setw(13) << (*iterUtil)->G_date() << (*iterUtil)->G_etablissement() << "\n";
         }
      }
   }

   return;
}

// ###################################################
// vueInterventionDate()
// Trier la liste d'interventions par date, croissante
// ###################################################
void Context::vueInterventionDate(ProfessionnelSante& pro)
{
   Trieur t;
   t.parDateAsc(*pro.G_lstInterventions());
   afficherListeInterventions(pro);
   system("pause");

   return;
}

// ###################################################
// vueInterventionDateDesc()
// Trier la liste d'interventions par date, décroissante
// ###################################################
void Context::vueInterventionDateDesc(ProfessionnelSante& pro)
{
   Trieur t;
   t.parDateDesc(*pro.G_lstInterventions());
   afficherListeInterventions(pro);
   system("pause");
   
   return;
}

// ###################################################
// vueInterventionEtablissement()
// Trier la liste d'interventions par établissement, croissante
// ###################################################
void Context::vueInterventionEtablissement(ProfessionnelSante& pro)
{
   Trieur t;
   t.parEtablissementAsc(*pro.G_lstInterventions());
   afficherListeInterventions(pro);
   system("pause");

   return;
}

// ###################################################
// vueInterventionEtablissement()
// Trier la liste d'interventions par établissement, décroissante
// ###################################################
void Context::vueInterventionEtablissementDesc(ProfessionnelSante& pro)
{
   Trieur t;
   t.parEtablissementDesc(*pro.G_lstInterventions());
   afficherListeInterventions(pro);
   system("pause");

   return;
}

// ###################################################
// vueInterventionEtablissement()
// Afficher la liste d'interventions
// ###################################################
void Context::vueInterventionBrut(ProfessionnelSante& pro)
{
   afficherListeInterventions(pro);
   system("pause");

   return;
}

// ###################################################
// Init()
// Démarrer la système de gestion de dossiers santés.
// ###################################################
void Context::Init()
{
   Indexeur.IndexationEstValide();
   ecranBienvenue();

   char Choix = menuPrincipal();
   while (Choix != 'Q')
   {
      switch (toupper(Choix))
      {
      case 'C': traiterCitoyen(); break;
      case 'P': traiterProfessionnel(); break;
      }
      Choix = menuPrincipal();
   }

   return;
}
