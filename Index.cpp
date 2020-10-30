// Index.cpp
// Définition de class "Index"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

#include "Biblio.h"

// ###################################################
// effacerIndexationErrone
// Remplacer des fichiers erronés avec des fichiers vides
// ###################################################
void Index::effacerIndexationErrone()
{
   ofstream fichierIndexCitoyens(FICHIER_INDEX_CITOYENS, ios::trunc);
   ofstream fichierIndexProfessionnels(FICHIER_INDEX_PROFESSIONNELS, ios::trunc);
   ofstream fichierIndexProblemes(FICHIER_INDEX_PROBLEMES, ios::trunc);
   ofstream fichierIndexUtilisations(FICHIER_INDEX_UTILISATIONS, ios::trunc);
   ofstream fichierIndexInterventions(FICHIER_INDEX_INTERVENTIONS, ios::trunc);
   ofstream fichierIndexPatients(FICHIER_INDEX_PATIENTS, ios::trunc);

   fichierIndexCitoyens.close();
   fichierIndexProfessionnels.close();
   fichierIndexProblemes.close();
   fichierIndexUtilisations.close();
   fichierIndexInterventions.close();
   fichierIndexPatients.close();

   return;
}

// ###################################################
// IndexationEstValide
// Valider l'indexation
// ###################################################
bool Index::IndexationEstValide()
{
   if (obtenirDateFichier(FICHIER_POPULATION) > obtenirDateFichier(FICHIER_INDEX_CITOYENS)
      || obtenirDateFichier(FICHIER_POPULATION) > obtenirDateFichier(FICHIER_INDEX_PROFESSIONNELS))
   {
      effacerIndexationErrone();
      return false;
   }
   return true;
}

// ###################################################
// chercherNombreDeLignesFichier
// Fonction utilitaire pour svaoir combien des lignes sont fans le fichier (pour pouvoir afficher un niveau de progrés)
// ###################################################
int Index::chercherNombreDeLignesFichier(string nomFichier)
{
   ifstream ficIn(nomFichier);
   int compteur = 0;
   string ligne;

   while (ficIn.good())
   {
      getline(ficIn, ligne);
      compteur++;
   }
   ficIn.close();
   return compteur;
}

// ###################################################
// estIndexeCitoyen
// Parcourir le fichier pour vérifier si un citoyen passé en paramétre est indexé
// ###################################################
bool Index::estIndexeCitoyen(string NAS)
{
   ifstream fichierIndexIn(FICHIER_INDEX_CITOYENS);
   string ligneCourante;

   NAS += ":";

   while (fichierIndexIn.good())
   {
      getline(fichierIndexIn, ligneCourante);
      if (ligneCourante.find(NAS) == 0)
         return true;
   }
   fichierIndexIn.close();
   return false;
}

// ###################################################
// IndexerCitoyen
// Indexer le citoyen 
// ###################################################
void Index::IndexerCitoyen(string NAS, int position)
{
   ofstream fichierIndexOut(FICHIER_INDEX_CITOYENS, ios::app);
   
   fichierIndexOut << NAS << ":" << position << "\n";

   fichierIndexOut.close();

   return;
}

// ###################################################
// estIndexeProfessionnel
// Vérifier si un professionnel de la santé est indexé
// ###################################################
bool Index::estIndexeProfessionnel(string codePS)
{
   ifstream fichierIndexIn(FICHIER_INDEX_PROFESSIONNELS);
   string ligneCourante;

   while (fichierIndexIn.good())
   {
      getline(fichierIndexIn, ligneCourante);
      if (ligneCourante.find(codePS) != -1)
         return true;
   }
   fichierIndexIn.close();
   return false;
}

// ###################################################
// IndexerProfessionnel
// Indexer le professionnel de la santé
// ###################################################
void Index::IndexerProfessionnel(string codePS, int position)
{
    ofstream fichierIndexOut(FICHIER_INDEX_PROFESSIONNELS, ios::app);
   
   fichierIndexOut << codePS << ":" << position << "\n";

   fichierIndexOut.close();

   return;
}

// ###################################################
// indexationEstAJour
// Fonctionnement originale de valider si l'indexation est à jour. 
// Elle a été déconseillée en faveur de d'une vérification plus compréhensive.
// ###################################################
bool Index::indexationEstAJour(const string nomFichierInfo, const string nomFichierIndex)
{
   string dateInfo = obtenirDateFichier(nomFichierInfo);
   string dateIndex = obtenirDateFichier(nomFichierIndex);

   if (dateIndex == fausseDate)
      return false;

   return dateIndex > dateInfo;
}

// ###################################################
// IndexerProblemes
// Indexer les problèmes d'un citoyen.
// ###################################################
void Index::IndexerProblemes(string NAS, vector<int> positions)
{
   ofstream fichierIndexOut(FICHIER_INDEX_PROBLEMES, ios::app);
   
   fichierIndexOut << NAS << ":";

   for (int i = 0; i < positions.size(); i++)
      fichierIndexOut << positions[i] << ";";
  
   fichierIndexOut << "\n";

   fichierIndexOut.close();

   return;
}

// ###################################################
// IndexerUtilisations
// Indexer les utilisations d'un citoyen.
// ###################################################
void Index::IndexerUtilisations(string NAS, vector<int> positions)
{
   ofstream fichierIndexOut(FICHIER_INDEX_UTILISATIONS, ios::app);

   fichierIndexOut << NAS << ":";

   for (int i = 0; i < positions.size(); i++)
      fichierIndexOut << positions[i] << ";";

   fichierIndexOut << "\n";

   fichierIndexOut.close();

   return;
}

// ###################################################
// IndexerUtilisations
// Indexer les patients d'un professionnel de la santé
// ###################################################
void Index::IndexerPatients(string codePS, vector<int> positions)
{
   ofstream fichierIndexOut(FICHIER_INDEX_PATIENTS, ios::app);

   fichierIndexOut << codePS << ":";

   for (int i = 0; i < positions.size(); i++)
      fichierIndexOut << positions[i] << ";";

   fichierIndexOut << "\n";

   fichierIndexOut.close();

   return;
}

// ###################################################
// IndexerInterventions
// Indexer les interventions d'un professionnel de la santé
// ###################################################
void Index::IndexerInterventions(string codePS, vector<int> positions)
{
   ofstream fichierIndexOut(FICHIER_INDEX_INTERVENTIONS, ios::app);

   fichierIndexOut << codePS << ":";

   for (int i = 0; i < positions.size(); i++)
      fichierIndexOut << positions[i] << ";";

   fichierIndexOut << "\n";

   fichierIndexOut.close();

   return;
}

// ###################################################
// retournerIndexCitoyen
// Retourner le position d'un citoyen
// ###################################################
int Index::retournerIndexCitoyen(string NAS)
{
   ifstream fichierIndexIn(FICHIER_INDEX_CITOYENS);
   string ligneCourante;
   Parseur<string> ParIndex(":");
   vector<string> valeurs;

   NAS += ":";

   while (fichierIndexIn.good())
   {
      getline(fichierIndexIn, ligneCourante);
      if (ligneCourante.find(NAS) == 0)
      {
         ParIndex.Decouper(ligneCourante, valeurs, 2);
         return stoi(valeurs[1]);
      }
   }
   fichierIndexIn.close();
   return -1;
}

// ###################################################
// retournerIndexProfessionnel
// Retourner le position d'un professionnel de la santé
// ###################################################
int Index::retournerIndexProfessionnel(string codePS)
{
   ifstream fichierIndexIn(FICHIER_INDEX_PROFESSIONNELS);
   string ligneCourante;
   Parseur<string> ParIndex(":");
   vector<string> valeurs;

   while (fichierIndexIn.good())
   {
      getline(fichierIndexIn, ligneCourante);
      if (ligneCourante.find(codePS) == 0)
      {
         ParIndex.Decouper(ligneCourante, valeurs, 2);
         return stoi(valeurs[1]);
      }
   }
   fichierIndexIn.close();
   return -1;
}

// ###################################################
// obtenirDateFichier
// retourner la date de dernière modification d'un fichier.
// ###################################################
string Index::obtenirDateFichier(string nomFichier)
{
   ifstream fichier(nomFichier);
   stringstream strTampon;
   if (fichier.good())
   {
      WIN32_FILE_ATTRIBUTE_DATA fileAttr;
      FILETIME ft, local_ft;
      SYSTEMTIME st;

      GetFileAttributesExA(nomFichier.c_str(), GetFileExInfoStandard, &fileAttr);
      ft = fileAttr.ftLastWriteTime;
      FileTimeToLocalFileTime(&ft, &local_ft);
      FileTimeToSystemTime(&local_ft, &st);

      strTampon << setfill('0');
      strTampon << right;
      strTampon << setw(4) << st.wYear << "-" << setw(2) << st.wMonth << "-" << setw(2) << st.wDay << " "
         << setw(2) << st.wHour << ":" << setw(2) << st.wMinute << ":" << setw(2) << st.wSecond << ":" << setw(3) << st.wMilliseconds;
      return strTampon.str();
   }
   return fausseDate;
}
