// Maladie.cpp
// Définition de class "Maladie"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

#include "Biblio.h"

// ###################################################
// Constructeur paramétrée
// ###################################################
Maladie::Maladie(vector<string> valeurs)
{
   NAS = stoi(valeurs[0]);
   pathologie = valeurs[1];
   dateDebut = valeurs[2];
   dateFin = valeurs[3];
   description = valeurs[4];
   stade = stoi(valeurs[5]);
}

// ###################################################
// Afficher
// Afficher les détails d'une maladie.
// ###################################################
void Maladie::Afficher()
{
   cout << left;
   cout << setw(22) << pathologie << setw(6) << stade << setw(12) << dateDebut << setw(12) << dateFin << description << endl;

   return;
}

// ###################################################
// G_typeProbleme
// Retourner le type de problème, en string
// ###################################################
string Maladie::G_typeProbleme()
{
   return "Maladie";
}
