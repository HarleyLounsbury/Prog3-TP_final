// Blessure.h
// D�claration de class "Blessure"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

class Blessure : public Probleme
{
   string type;

public:
   Blessure(vector<string> valeurs);

   void Afficher();
   string G_typeProbleme();
};