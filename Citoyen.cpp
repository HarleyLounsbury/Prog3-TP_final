// Citoyen.cpp
// Définition de class "Citoyen"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

#include "Biblio.h"


// ###################################################
// Constructeur par défaut
// ###################################################
Citoyen::Citoyen()
{
   NAS = -1;
   nom = "Inconnu";
   naissance = "0000-00-00";
}

// ###################################################
// Constructeur paramétré
// Version citoyen (chargement de données rélatifs au dossier du citoyen)
// ###################################################
Citoyen::Citoyen(vector<string> valeurs, bool estIndexe)
{
   NAS = stoi(valeurs[0]);
   nom = valeurs[1];
   naissance = valeurs[2];

   if (!estIndexe)
   {
      importerProblemesNonIndexes();
      importerUtilisationsNonIndexes();
   }
   if (estIndexe)
   {
      importerProblemesIndexes();
      importerUtilisationsIndexes();
   }
   formatterNom();
}

// ###################################################
// Constructeur paramétré
// Version patient 
// ###################################################
Citoyen::Citoyen(vector<string> valeurs, bool estPro, bool estIndexe)
{
   NAS = stoi(valeurs[0]);
   nom = valeurs[1];
   naissance = valeurs[2];
   formatterNom();
}

// ###################################################
// Déstructeur
// ###################################################
Citoyen::~Citoyen()
{
   list<Probleme*>::iterator itProb = lstProbleme.begin();
   Probleme* probASupprimer;
   for (itProb; itProb != lstProbleme.end(); itProb++)
   {
      probASupprimer = *(itProb);
      delete probASupprimer;
   }

   list<Utilisation*>::iterator itUtil = lstUtilisations.begin();
   Utilisation* utilASupprimer;
   for (itUtil; itUtil != lstUtilisations.end(); itUtil++)
   {
      utilASupprimer = *(itUtil);
      delete utilASupprimer;
   }
}

// ###################################################
// G_nom
// retourne le nom du citoyen
// ###################################################
string Citoyen::G_nom()
{
   return nom;
}

// ###################################################
// G_naissance
// retourne la date de naissance du citoyen
// ###################################################
string Citoyen::G_naissance()
{
   return naissance;
}

// ###################################################
// G_NAS
// retourne le NAS du citoyen
// ###################################################
int Citoyen::G_NAS()
{
   return NAS;
}

// ###################################################
// G_nbProblemes
// retourne le nombre de problèmes du citoyen
// ###################################################
int Citoyen::G_nbProblemes()
{
   return lstProbleme.size();
}

// ###################################################
// G_nbUtilisations
// retourne le nombre de utilisations du citoyen
// ###################################################
int Citoyen::G_nbUtilisations()
{
   return lstUtilisations.size();
}

// ###################################################
// G_nbRendezvous
// retourne le nombre de rendez-vous du citoyen
// ###################################################
int Citoyen::G_nbRendezvous()
{
   int compteur = 0;
   
   list<Utilisation*>::iterator iter = lstUtilisations.begin();
   for (iter; iter != lstUtilisations.end(); iter++)
      if ((*iter)->G_typeUtilisation() == "Rendezvous")
         compteur++;

   return compteur;
}

// ###################################################
// G_nbHospitalisations
// retourne le nombre d'hospitalisations du citoyen
// ###################################################
int Citoyen::G_nbHospitalisations()
{
   int compteur = 0;

   list<Utilisation*>::iterator iter = lstUtilisations.begin();
   for (iter; iter != lstUtilisations.end(); iter++)
      if ((*iter)->G_typeUtilisation() == "Hospitalisation")
         compteur++;

   return compteur;
}

// ###################################################
// AfficherBlessures
// Afficher les blessures du citoyen
// ###################################################
void Citoyen::AfficherBlessures()
{
   cout << left;
   cout << setw(13) << "Type" << setw(12) << "Début" << setw(11) << "Guérison" << "Description" << endl;
   cout << setw(62) << setfill('_') << "_" << setfill(' ') << endl;
   
   list<Probleme*>::iterator iter = lstProbleme.begin();
   for (iter; iter != lstProbleme.end(); iter++)
   {
      if ((*iter)->G_typeProbleme() == "Blessure")
         (*iter)->Afficher();
   }
      
   return;
}

// ###################################################
// AfficherMaladies
// Afficher les maladies du citoyen
// ###################################################
void Citoyen::AfficherMaladies()
{
   cout << left;
   cout << setw(22) << "Pathologie" << setw(6) << "Stade" << setw(12) << "Début" << setw(12) << "Guérison" << "Commentaire" << endl;
   cout << setw(62) << setfill('_') << "_" << setfill(' ') << endl;

   list<Probleme*>::iterator iter = lstProbleme.begin();
   for (iter; iter != lstProbleme.end(); iter++)
   {
      if ((*iter)->G_typeProbleme() == "Maladie")
         (*iter)->Afficher();
   }

   return;
}

// ###################################################
// AfficherRendezvous
// Afficher les rendez-vous du citoyen
// ###################################################
void Citoyen::AfficherRendezvous()
{
   cout << left;
   cout << setw(31) << "Établissement" << setw(13) << "Date" << "Code PS" << endl;
   cout << setw(62) << setfill('_') << "_" << setfill(' ') << endl;

   list<Utilisation*>::iterator iter = lstUtilisations.begin();
   for (iter; iter != lstUtilisations.end(); iter++)
   {
      if ((*iter)->G_typeUtilisation() == "Rendezvous")
         (*iter)->Afficher();
   }

   return;
}

// ###################################################
// AfficherHospitalisations
// Afficher les hospitalisations du citoyen
// ###################################################
void Citoyen::AfficherHospitalisations()
{
   cout << left;
   cout << setw(31) << "Établissement" << setw(13) << "Arrivée" << setw(14) << "Code PS" << setw(8) << "Chambre" << "Départ" << endl;
   cout << setw(62) << setfill('_') << "_" << setfill(' ') << endl;

   list<Utilisation*>::iterator iter = lstUtilisations.begin();
   for (iter; iter != lstUtilisations.end(); iter++)
   {
      if ((*iter)->G_typeUtilisation() == "Hospitalisation")
         (*iter)->Afficher();
   }

   return;
}

// ###################################################
// importerProblemesNonIndexes
// Mechanism d'importation de données non-indexés
// ###################################################
void Citoyen::importerProblemesNonIndexes()
{
   ifstream ficIn(FICHIER_PROBLEMES);
   string ligneCourante;
   Parseur<Probleme> ParPro(";");
   vector<string> valeurs;
   int nbChamps;
   int compteur = 0;
   vector<int> positions;
   int positionTotale = 0;
   time_t now = time(0);

   string stringNAS = to_string(NAS) + ";";
   while (ficIn.good())
   {
      getline(ficIn, ligneCourante);
      if (ligneCourante.find(stringNAS) == 0)
      {
         compteur++;
         if (time(0) - now > 1)
            cout << "Chargement de Probleme " << compteur << "\r";
         nbChamps = ParPro.CompteurChamp(ligneCourante) + 1;
         ParPro.Decouper(ligneCourante, valeurs, nbChamps);
         if (valeurs[0] == to_string(NAS))
            lstProbleme.emplace_front(UP.CreerProbleme(valeurs));
         valeurs.clear();
         positions.emplace_back(positionTotale);
      }
      positionTotale += ligneCourante.length();
      positionTotale += 2; // Pour le \n en fin de ligne.
   }
   Indexeur.IndexerProblemes(to_string(NAS), positions);
   cout << setw(60) << setfill(' ') << " " << "\r";
   ficIn.close();
   return;
}

// ###################################################
// importerUtilisationsNonIndexes
// Mechanism d'importation de données non-indexés
// ###################################################
void Citoyen::importerUtilisationsNonIndexes()
{
   ifstream ficIn(FICHIER_UTILISATIONS);
   string ligneCourante;
   Parseur<Utilisation> ParUtil(";");
   vector<string> valeurs;
   int nbChamps;
   string stringNAS = to_string(NAS) + ";";
   int compteur = 0;
   vector<int> positions;
   int positionTotale = 0; 
   time_t now = time(0);

   while (ficIn.good())
   {
      getline(ficIn, ligneCourante);
      if (ligneCourante.find(stringNAS) == 0)
      {
         compteur++;
         if (time(0) - now > 1)
            cout << "Chargement de utilisation " << compteur << "\r";
         nbChamps = ParUtil.CompteurChamp(ligneCourante) + 1;
         ParUtil.Decouper(ligneCourante, valeurs, nbChamps);
         if (valeurs[0] == to_string(NAS))
         {
            lstUtilisations.emplace_front(UU.CreerUtilisation(valeurs));
         }
         valeurs.clear();
         positions.emplace_back(positionTotale);
      }
      positionTotale += ligneCourante.length();
      positionTotale += 2; // Pour le \n en fin de ligne.
   }
   Indexeur.IndexerUtilisations(to_string(NAS), positions);

   ficIn.close();
   return;
}

// ###################################################
// importerProblemesIndexes
// Mechanism d'importation de données indexés
// ###################################################
void Citoyen::importerProblemesIndexes()
{
   string ligne;
   ifstream fichierIndexIn(FICHIER_INDEX_PROBLEMES);
   Parseur<Probleme> ParPro(";");
   vector<string> valeurs;
   int nbChamps;
   int compteur = 0;
   string stringNAS = to_string(NAS) + ":";
   vector<string> positions;

   while (fichierIndexIn.good())
   {
      getline(fichierIndexIn, ligne);
      if (ligne.find(stringNAS) == 0)
      {
         fichierIndexIn.close();
         ligne = ligne.substr(stringNAS.length());
         nbChamps = ParPro.CompteurChamp(ligne);
         ParPro.Decouper(ligne, positions, nbChamps);
         ifstream fichierProblemesIn(FICHIER_PROBLEMES);
         for (int i = 0; i < positions.size(); i++)
         {
            compteur++;
            cout << "Chargement de Probleme " << compteur << "\r";
            fichierProblemesIn.seekg(stoi(positions[i]));
            getline(fichierProblemesIn, ligne);
            nbChamps = ParPro.CompteurChamp(ligne) + 1;
            ParPro.Decouper(ligne, valeurs, nbChamps);
            lstProbleme.emplace_front(UP.CreerProbleme(valeurs));
            valeurs.clear();
         }
         fichierProblemesIn.close();
      }
      cout << setw(60) << setfill(' ') << " " << "\r";
   }
   return;
}

// ###################################################
// importerUtilisationsIndexes
// Mechanism d'importation de données indexés
// ###################################################
void Citoyen::importerUtilisationsIndexes()
{
   string ligne;
   ifstream fichierIndexIn(FICHIER_INDEX_UTILISATIONS);
   Parseur<Utilisation> ParUtil(";");
   vector<string> valeurs;
   int nbChamps;
   int compteur = 0;
   string stringNAS = to_string(NAS) + ":";
   vector<string> positions;
   time_t now = time(0);

   while (fichierIndexIn.good())
   {
      getline(fichierIndexIn, ligne);
      if (ligne.find(stringNAS) == 0)
      {
         fichierIndexIn.close();
         ligne = ligne.substr(stringNAS.length());
         nbChamps = ParUtil.CompteurChamp(ligne);
         ParUtil.Decouper(ligne, positions, nbChamps);
         ifstream fichierUtilisationsIn(FICHIER_UTILISATIONS);
         for (int i = 0; i < positions.size(); i++)
         {
            compteur++;
            if (time(0) - now > 1)
            {
               cout << "Chargement de Probleme " << compteur << "\r";
            }
            fichierUtilisationsIn.seekg(stoi(positions[i]));
            getline(fichierUtilisationsIn, ligne);
            nbChamps = ParUtil.CompteurChamp(ligne) + 1;
            ParUtil.Decouper(ligne, valeurs, nbChamps);
            lstUtilisations.emplace_front(UU.CreerUtilisation(valeurs));
            valeurs.clear();
         }
         fichierUtilisationsIn.close();
      }
      cout << setw(60) << setfill(' ') << " " << "\r";
   }
   return;
}

// ###################################################
// formatterNom
// Formatter le nom pour que les premiers lettre soivent en majuscule
// ###################################################
void Citoyen::formatterNom()
{
   nom[0] = toupper(nom[0]);
   for (unsigned int i = 1; i < nom.length(); i++)
      if (nom[i] == ' ')
         nom[i + 1] = toupper(nom[i + 1]);
   return;
}
