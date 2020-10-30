// Probleme.cpp
// D�finition de class "Probleme"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

#include "Biblio.h"

// ###################################################
// Instancier un probl�me, selon l'information pass� en param�tre.
// ###################################################
Probleme* UsineProbleme::CreerProbleme(vector<string> valeurs)
{
   if (valeurs.size() == 5)
      return new Blessure(valeurs);
   if (valeurs.size() == 6)
      return new Maladie(valeurs);

   return nullptr;
}
