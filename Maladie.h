// Maladie.h
// Déclaration de class "Maladie"
// Auteur: Harley Lounsbury
// Date: 2019-12-16


class Maladie : public Probleme
{
private:
   string pathologie;
   int stade;

public:
   Maladie(vector<string> valeurs);

   void Afficher();
   string G_typeProbleme();
};