// Utilisation.cpp
// D�finition de class "Utilisation"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

#include "Biblio.h"

// ###################################################
// Constructeur par d�faut. 
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
// Retourner le NAS associ� � l'intervention
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
// Retourner l'�tablissement de l'utilisation
// ###################################################
string Utilisation::G_etablissement()
{
   return etablissement;
}

