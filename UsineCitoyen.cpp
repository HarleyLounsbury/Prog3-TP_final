// Citoyen.cpp
// D�finition de class "Citoyen"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

#include "Biblio.h"

// ###################################################
// Instancier un citoyen, selon l'information pass� en param�tre.
// ###################################################
Citoyen* UsineCitoyen::CreerCitoyen(vector<string> valeurs, bool estIndexe)
{
   return new Citoyen(valeurs, estIndexe);
}

// ###################################################
// Instancier un patient, selon l'information pass� en param�tre.
// ###################################################
Citoyen* UsineCitoyen::CreerPatient(vector<string> valeurs, bool estIndexe)
{
   return new Citoyen(valeurs, true, estIndexe);
}
