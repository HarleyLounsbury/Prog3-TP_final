// ProfessionnelSante.cpp
// Définition de class "ProfessionnelSante"
// Auteur: Harley Lounsbury
// Date: 2019-12-16
/*
Alain,
les fonctions pour charger les données ici sont...particulières. Aprés l'avoir mis fonctionnel, mon but c'était la performance. 
Quelques considerations et techniques appris durant mes recherches et tests unitaires (il y eu plusieurs).
En considerant le nombre de données à charger (pas un petit nombre, mais pas dans les millions non-plus):
- La hierarchie de rapidité de mémoire: 1. L1/L2  2. RAM  3. Disque
Quand possible, faire la manipulation de données avec la mémoire le plus rapide possible. 

Le STL à quelques particulièrités:
- Quand l'ordre n'est pas important, ajouter en avant d'une liste, et au but d'un vector. 
- emplace_front pour une liste et emplace_back pour le vector sont de, en moyenne sur mon i7 + 8Go DRAM, 3.8% plus rapide.
- quand-on connais le grandeur d'un vector, utiliser reserve(). Ceci enleve beaucoup d'opérations à long...allocation de nouveau contenant, copie le contenu, vider l'ancien contenu, désallocation. 
- Parcourir les vectors par indice. On a vu ca en classe, c'est trés efficace. 

Autre:
- Quand on boucle sur beaucoup de données, effectuer seulement les opérations qui sont absolument nécessaires (un concatination répété milliers de fois est fatal).
- Pour ce que j'ai pû tester, ça inclus aussi la limite de la boucle (le pointeur va chercher plus rapidement la donnée stocké dans un variable, que de parcourir le contenant pour sa grandeur, à ces grandeurs)
- Quand, par exemple, la limite est quelque chose calculé, l'inverse est vrai. Le processeur peut calculer cette réponse même plus vite que le pointeur en mémoire vive.
- à quelque places, les int déclarés dans les boucles FOR générent des warning (signed/unsigned). Le changement en unsigned int font ralentir l'opération. Je n'ai pas d'hypothèse, car selon le documentation ce ne devrait pas, mais je l'ai vu en pratique. 
- Ce dernier est particulièrement vrai dans importerPatientsNonIndexe, dans la boucle FOR imbriquée (j < totalPopulation).


*/

#include "Biblio.h"

// ###################################################
// NASExiste
// Vérifier l'existence d'un NAS dans notre répertoire des NAS (pas de doublons!)
// ###################################################
bool ProfessionnelSante::NASExiste(string NAS)
{
   NAS += ";";
   for (unsigned int i = 0; i < NASPatients.size(); i++)
   {
      if ((NAS) == NASPatients[i])
         return true;
   }
   return false;
}

// ###################################################
// importerPatientsIndexes
// Méchanism de chargement de patients quand ils sont indexés
// ###################################################
void ProfessionnelSante::importerPatientsIndexes()
{
   ifstream fichierIndexIn(FICHIER_INDEX_PATIENTS);
   string ligne;
   Parseur<Citoyen> ParCit(";");
   int nbChamps;
   vector<string> valeurs;
   vector<string> positions;

   while (fichierIndexIn.good())
   {
      getline(fichierIndexIn, ligne);
      if (ligne.find(codePS) != -1)
         break;
   }

   ligne = ligne.substr(codePS.length() + 1);
   nbChamps = ParCit.CompteurChamp(ligne);
   ParCit.Decouper(ligne, positions, nbChamps);

   int totalPatients = positions.size();
   int calc = 0;

   ifstream fichierPopIn(FICHIER_POPULATION);
   for (unsigned int i = 0; i < positions.size(); i++)
   {
      // Pas nécessaire: temps de chargement en test unitaire: <1s
      // calc = (double)i * 100 / totalPatients;
      // cout << "Importation de patients\t" << setprecision(2) << calc << "%\r";
      fichierPopIn.seekg(stoi(positions[i]));
      getline(fichierPopIn, ligne);
      nbChamps = ParCit.CompteurChamp(ligne) + 1;
      ParCit.Decouper(ligne, valeurs, nbChamps);
      lstPatients.emplace_front(UC.CreerPatient(valeurs, true));
      valeurs.clear();
   }
   fichierPopIn.close();
   cout << setw(60) << setfill(' ') << " " << "\r";

   return;
}

// ###################################################
// importerInterventionsIndexes
// Méchanism de chargement d'interventions quand ils sont indexés
// ###################################################
void ProfessionnelSante::importerInterventionsIndexes()
{
   ifstream fichierIndexIn(FICHIER_INDEX_INTERVENTIONS);
   string ligne;
   Parseur<Utilisation> ParUtil(";");
   int nbChamps;
   vector<string> valeurs;
   vector<string> positions;

   while (fichierIndexIn.good())
   {
      getline(fichierIndexIn, ligne);
      if (ligne.find(codePS) != -1)
         break;
   }

   ligne = ligne.substr(codePS.length() + 1);
   nbChamps = ParUtil.CompteurChamp(ligne);
   ParUtil.Decouper(ligne, positions, nbChamps);

   int totalInterventions = positions.size();
   int calc = 0;

   ifstream fichierUtilIn(FICHIER_UTILISATIONS);
   for (unsigned int i = 0; i < positions.size(); i++)
   {
      // Possible affichage de progrés, temps de charger pendant les tests unitaire: <1s
      // calc = (double)i * 100 / totalInterventions;
      // cout << "Importation de interventions\t" << setprecision(2) << calc << "%\r";
      fichierUtilIn.seekg(stoi(positions[i]));
      getline(fichierUtilIn, ligne);
      nbChamps = ParUtil.CompteurChamp(ligne) + 1;
      ParUtil.Decouper(ligne, valeurs, nbChamps);
      lstInterventions.emplace_front(UU.CreerUtilisation(valeurs));
      valeurs.clear();
   }
   fichierUtilIn.close();
   cout << setw(60) << setfill(' ') << " " << "\r";

   return;
}

// ###################################################
// importerInterventionsNonIndexes
// Méchanism de chargement d'interventions quand ils ne sont pas indexés
// C'est ici que la magie se passe -> temps moyenne de chargement ~1.8s
// ###################################################
void ProfessionnelSante::importerInterventionsNonIndexes()
{
   ifstream ficIn(FICHIER_UTILISATIONS);
   string ligneCourante;
   vector<string> utilisations;
   Parseur<Utilisation> ParUtil(";");
   vector<string> valeurs;
   int nbChamps;
   vector<int> positions;
   int positionTotale = 0;
   int calc = 0;

   cout << "Importation d'interventions - " << setprecision(2) << calc << "%\r";
   time_t now = time(0);

   utilisations.reserve(Indexeur.chercherNombreDeLignesFichier(FICHIER_UTILISATIONS));
   while (ficIn.good())
   {
      getline(ficIn, ligneCourante);
      utilisations.emplace_back(ligneCourante);
      if (ligneCourante.find(codePS) != -1)
      {
         positions.emplace_back(positionTotale);
      }
      positionTotale += ligneCourante.length();
      positionTotale += 2; // Pour le \n en fin de ligne.
   }
   ficIn.close();
   
   unsigned int total = utilisations.size();
   
   for(int i = 0; i < total; i++)
   {
      if (utilisations[i].find(codePS) != -1)
      {
         if (time(0) - now > 1)
         {
            calc = i * 100 / total;
            cout << "Importation d'interventions - "<< setprecision(2) << calc << "%\r";
            now = time(0);
         }
         nbChamps = ParUtil.CompteurChamp(utilisations[i]) + 1;
         ParUtil.Decouper(utilisations[i], valeurs, nbChamps);
         if (!NASExiste(valeurs[0]))
            NASPatients.emplace_back(valeurs[0] + ";");

         lstInterventions.emplace_front(UU.CreerUtilisation(valeurs));
      }
      valeurs.clear();
   }
   Indexeur.IndexerInterventions(codePS, positions);
   cout << setw(50) << setfill(' ') << " " <<"\r";
   return;
}

// ###################################################
// importerPatientsNonIndexes
// Méchanism de chargement de patients quand ils ne sont pas indexés
// C'est ici que la magie se passe -> temps moyenne de chargement ~2.5s
// ###################################################
void ProfessionnelSante::importerPatientsNonIndexes()
{
   ifstream ficIn(FICHIER_POPULATION);
   string ligneCourante;
   vector<string> population;
   Parseur<Citoyen> ParCit(";");
   vector<string> valeurs;
   vector<int> positionsPop;
   vector<int> positionsRetenue;
   int positionTotale = 0;
   int calc = 0;

   population.reserve(Indexeur.chercherNombreDeLignesFichier(FICHIER_POPULATION));

   while (ficIn.good())
   {
      positionsPop.emplace_back(positionTotale);
      getline(ficIn, ligneCourante);
      population.emplace_back(ligneCourante);
      positionTotale += ligneCourante.length() + 2;
   }
   ficIn.close();

   time_t now = time(0);
   int totalPatients = NASPatients.size();
   int totalPopulation = population.size();
   
   for (unsigned int i = 0; i < totalPatients; i++)
   {
      if (time(0) - now > 1)
      {
         calc = i * 100 / totalPatients;
         cout << "Importation de patients\t" << setprecision(2) << calc << "%\r";
         now = time(0);
      }
      for (unsigned int j = 0; j < totalPopulation; j++)
      {
         if (population[j].find(NASPatients[i]) == 0)
         {
            ParCit.Decouper(population[j], valeurs, 3);
            lstPatients.emplace_front(UC.CreerPatient(valeurs, false));
            positionsRetenue.emplace_back(positionsPop[j]);
            valeurs.clear();
            break;
         }
      }
   }
   cout << setw(60) << setfill(' ') << " " << "\r";

   Indexeur.IndexerPatients(codePS, positionsRetenue);

   return;
}

// ###################################################
// Constructeur 
// ###################################################
ProfessionnelSante::ProfessionnelSante(vector<string> valeurs, bool estIndexe) : Citoyen(valeurs, true, estIndexe)
{
   codePS = valeurs[3];
   titre = valeurs[4];

   cout << "Chargement de données en cours...\n";
   if (!estIndexe)
   {
      importerInterventionsNonIndexes();
      importerPatientsNonIndexes();
   }
   if (estIndexe)
   {
      importerInterventionsIndexes();
      importerPatientsIndexes();
   }
}

// ###################################################
// Déstructeur
// ###################################################
ProfessionnelSante::~ProfessionnelSante()
{
   list<Citoyen*>::iterator iterCit = lstPatients.begin();
   Citoyen* citASupprimer;
   for (iterCit; iterCit != lstPatients.end(); iterCit++)
   {
      citASupprimer = *iterCit;
      delete citASupprimer;
   }
   list<Utilisation*>::iterator iterInt = lstInterventions.begin();
   Utilisation* intASupprimer;
   for (iterInt; iterInt != lstInterventions.end(); iterInt++)
   {
      intASupprimer = *iterInt;
      delete intASupprimer;
   }
}

// ###################################################
// G_titre
// Retourner le titre du professionnel
// ###################################################
string ProfessionnelSante::G_titre()
{
   return titre;
}

// ###################################################
// G_lstPatients
// Retourner l'adresse de la liste de patients.
// ###################################################
list<Citoyen*>* ProfessionnelSante::G_lstPatients()
{
   return &lstPatients;
}

// ###################################################
// G_lstPatients
// Retourner l'adresse de la liste d'interventions.
// ###################################################
list<Utilisation*>* ProfessionnelSante::G_lstInterventions()
{
   return &lstInterventions;
}

// ###################################################
// CompteInterventionsPourPatient
// Retourner le nombre d'interventions pour un patient.
// ###################################################
int ProfessionnelSante::CompteInterventionsPourPatient(int NAS)
{
   int compteur = 0;

   list<Utilisation*>::iterator iter = lstInterventions.begin();
   list<Utilisation*>::iterator iterFin = lstInterventions.end();

   for (iter; iter != iterFin; iter++)
   {
      if ((*iter)->G_NAS() == NAS)
         compteur++;
   }

   return compteur;
}
