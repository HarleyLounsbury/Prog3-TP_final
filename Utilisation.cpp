// Utilisation.cpp
// Définition de class "Utilisation"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

#include "Biblio.h"

// ###################################################
// Constructeur par défaut. 
// ###################################################
Utilisation::Utilisation()
{
   NAS = -1;
   codePS = "Inconnu";
   etablissement = "Inconnu";
   date = "0000-00-00";
}

// ###################################################
// G_NAS
// Retourner le NAS associé à l'intervention
// ###################################################
int Utilisation::G_NAS()
{
   return NAS;
}

// ###################################################
// G_date
// Retourner la date de l'utilisation
// ###################################################
string Utilisation::G_date()
{
   return date;
}

// ###################################################
// G_etablissement
// Retourner l'établissement de l'utilisation
// ###################################################
string Utilisation::G_etablissement()
{
   return etablissement;
}

