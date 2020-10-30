// Rendezvous.cpp
// D�finition de class "Rendezvous"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

#include "Biblio.h"

// ###################################################
// Constructeur param�tr�e
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
// Afficher les d�tails d'un rendez-vous.
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
