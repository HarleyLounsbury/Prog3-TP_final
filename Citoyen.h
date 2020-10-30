// Citoyen.h
// Déclaration de class "Citoyen"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

class Citoyen
{
protected:
   int NAS;
   string nom;
   string naissance;

   list<Probleme*> lstProbleme;
   list<Utilisation*> lstUtilisations;

   void importerProblemesNonIndexes();
   void importerUtilisationsNonIndexes();
   void importerProblemesIndexes();
   void importerUtilisationsIndexes();

   void formatterNom();

public:
   Citoyen();
   Citoyen(vector<string> valeurs, bool estIndexe);
   Citoyen(vector<string> valeurs, bool estPro, bool estIndexe);
   virtual ~Citoyen();

   string G_nom();
   string G_naissance();
   int G_NAS();

   int G_nbProblemes();
   int G_nbUtilisations();
   int G_nbRendezvous();
   int G_nbHospitalisations();

   void AfficherBlessures();
   void AfficherMaladies();
   void AfficherRendezvous();
   void AfficherHospitalisations();

};