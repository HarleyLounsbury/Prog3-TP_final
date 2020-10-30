// Probleme.cpp
// Définition de class "Probleme"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

#include "Biblio.h"

// ###################################################
// Instancier un problème, selon l'information passé en paramétre.
// ###################################################
Probleme* UsineProbleme::CreerProbleme(vector<string> valeurs)
{
   if (valeurs.size() == 5)
      return new Blessure(valeurs);
   if (valeurs.size() == 6)
      return new Maladie(valeurs);

   return nullptr;
}
