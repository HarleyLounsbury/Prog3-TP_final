// Utilisation.cpp
// Définition de class "Utilisation"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

#include "Biblio.h"

// ###################################################
// Instancier une utilisation, selon l'information passé en paramétre.
// ###################################################
Utilisation* UsineUtilisation::CreerUtilisation(vector<string> valeurs)
{
   if (valeurs.size() == 4)
      return new Rendezvous(valeurs);
   if (valeurs.size() == 6)
      return new Hospitalisation(valeurs);

   return nullptr;
}
