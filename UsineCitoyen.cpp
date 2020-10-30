// Citoyen.cpp
// Définition de class "Citoyen"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

#include "Biblio.h"

// ###################################################
// Instancier un citoyen, selon l'information passé en paramétre.
// ###################################################
Citoyen* UsineCitoyen::CreerCitoyen(vector<string> valeurs, bool estIndexe)
{
   return new Citoyen(valeurs, estIndexe);
}

// ###################################################
// Instancier un patient, selon l'information passé en paramétre.
// ###################################################
Citoyen* UsineCitoyen::CreerPatient(vector<string> valeurs, bool estIndexe)
{
   return new Citoyen(valeurs, true, estIndexe);
}
