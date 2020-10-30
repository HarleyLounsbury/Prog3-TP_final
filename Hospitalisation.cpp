// Hospitalisation.cpp
// Définition de class "Hospitalisation"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

#include "Biblio.h"

// ###################################################
// Constructeur paramétré
// ###################################################
Hospitalisation::Hospitalisation(vector<string> valeurs)
{
   NAS = stoi(valeurs[0]);
   codePS = valeurs[1];
   etablissement = valeurs[2];
   date = valeurs[3];
   dateFin = valeurs[4];
   chambre = stoi(valeurs[5]);
}

// ###################################################
// Afficher
// Afficher les informations
// ###################################################
void Hospitalisation::Afficher()
{
   cout << left;
   cout << setw(31) << etablissement << setw(13) << date << setw(14) << codePS << setw(8) << chambre << dateFin << endl;

   return;
}

// ###################################################
// G_typeUtilisation
// Retourner le type de utilisation, en string
// ###################################################
string Hospitalisation::G_typeUtilisation()
{
   return "Hospitalisation";
}
