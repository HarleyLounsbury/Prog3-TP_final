// Utilisation.h
// Déclaration de class "Utilisation"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

class Utilisation
{
protected:
   int NAS;
   string codePS;
   string etablissement;
   string date;

public:
   Utilisation();
   virtual void Afficher() = 0;
   virtual string G_typeUtilisation() = 0;

   int G_NAS();
   string G_date();
   string G_etablissement();
};
