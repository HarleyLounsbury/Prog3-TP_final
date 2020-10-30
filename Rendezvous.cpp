// Rendezvous.cpp
// Définition de class "Rendezvous"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

#include "Biblio.h"

// ###################################################
// Constructeur paramétrée
// ###################################################
Rendezvous::Rendezvous(vector<string> valeurs)
{
   NAS = stoi(valeurs[0]);
   codePS = valeurs[1];
   etablissement = valeurs[2];
   date = valeurs[3];
}

// ###################################################
// Afficher
// Afficher les détails d'un rendez-vous.
// ###################################################
void Rendezvous::Afficher()
{
   cout << left;
   cout << setw(31) << etablissement << setw(13) << date << codePS << endl;

   return;
}

// ###################################################
// G_typeUtilisation
// retourner le type d'utilisation, en string.
// ###################################################
string Rendezvous::G_typeUtilisation()
{
   return "Rendezvous";
}
