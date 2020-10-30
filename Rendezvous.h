// Rendezvous.h
// Déclaration de class "Rendezvous"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

class Rendezvous : public Utilisation
{

public:
   Rendezvous(vector<string> valeurs);

   void Afficher();
   string G_typeUtilisation();
};