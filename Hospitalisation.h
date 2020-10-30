// Hospitalisation.h
// Déclaration de class "Hospitalisation"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

class Hospitalisation : public Utilisation
{
private:
   string dateFin;
   int chambre;

public:
   Hospitalisation(vector<string> valeurs);

   void Afficher();
   string G_typeUtilisation();
};