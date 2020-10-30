// Probleme.h
// Déclaration de class abstrait "Probleme"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

class Probleme
{
protected:
   int NAS;
   string dateDebut;
   string dateFin;
   string description;

public:
   virtual void Afficher() = 0;
   virtual string G_typeProbleme() = 0;
};