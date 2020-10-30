// Blessure.cpp
// D�finition de class "Blessure"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

#include "Biblio.h"

// ###################################################
// Constructeur param�tr�
// ###################################################
Blessure::Blessure(vector<string> valeurs)
{
   NAS = stoi(valeurs[0]);
   type = valeurs[1];
   dateDebut = valeurs[2];
   dateFin = valeurs[3];
   description = valeurs[4];
}

// ###################################################
// Afficher()
// Afficher les d�tails.
// ###################################################
void Blessure::Afficher()
{
   cout << left;
   cout << setw(13) << type << setw(12) << dateDebut << setw(11) << dateFin << description << endl;

   return;
}

// ###################################################
// G_typeProbleme()
// Retourner string qui d�crit le type.
// ###################################################
string Blessure::G_typeProbleme()
{
   return "Blessure";
}
