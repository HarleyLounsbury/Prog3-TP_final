// Trieur.cpp
// D�finition de class "Trieur"
// Auteur: Harley Lounsbury
// Date: 2019-12-16

#include "Biblio.h"

// ###################################################
// Trier la liste par date de naissance, croissante
// ###################################################
void Trieur::parNaissanceAsc(list<Citoyen*>& lst)
{
   struct comp
   {
      bool operator()(Citoyen* a, Citoyen* b)
      {
         return (*a).G_naissance() < (*b).G_naissance();
      }
   };

   lst.sort(comp());

   return;
}

// ###################################################
// Trier la liste par date de naissance, d�croissante
// ###################################################
void Trieur::parNaissanceDesc(list<Citoyen*>& lst)
{
   struct comp
   {
      bool operator()(Citoyen* a, Citoyen* b)
      {
         return (*a).G_naissance() > (*b).G_naissance();
      }
   };

   lst.sort(comp());

   return;
}

// ###################################################
// Trier la liste par NAS, croissante
// ###################################################
void Trieur::parNASAsc(list<Citoyen*>& lst)
{
   struct comp
   {
      bool operator()(Citoyen* a, Citoyen* b)
      {
         return (*a).G_NAS() < (*b).G_NAS();
      }
   };

   lst.sort(comp());

   return;
}

// ###################################################
// Trier la liste par NAS, d�croissante
// ###################################################
void Trieur::parNASDesc(list<Citoyen*>& lst)
{
   struct comp
   {
      bool operator()(Citoyen* a, Citoyen* b)
      {
         return (*a).G_NAS() > (*b).G_NAS();
      }
   };

   lst.sort(comp());

   return;
}

// ###################################################
// Trier la liste par nom, croissante
// ###################################################
void Trieur::parNomAsc(list<Citoyen*>& lst)
{
   struct comp
   {
      bool operator()(Citoyen* a, Citoyen* b)
      {
         return (*a).G_nom() < (*b).G_nom();
      }
   };

   lst.sort(comp());

   return;
}

// ###################################################
// Trier la liste par nom, d�croissante
// ###################################################
void Trieur::parNomDesc(list<Citoyen*>& lst)
{
   struct comp
   {
      bool operator()(Citoyen* a, Citoyen* b)
      {
         return (*a).G_nom() > (*b).G_nom();
      }
   };

   lst.sort(comp());

   return;
}

// ###################################################
// Trier la liste par date de l'utilisation, croissante
// ###################################################
void Trieur::parDateAsc(list<Utilisation*>& lst)
{
   struct comp
   {
      bool operator()(Utilisation* a, Utilisation* b)
      {
         return (*a).G_date() < (*b).G_date();
      }
   };

   lst.sort(comp());

   return;
}

// ###################################################
// Trier la liste par date de l'utilisation, d�croissante
// ###################################################
void Trieur::parDateDesc(list<Utilisation*>& lst)
{
   struct comp
   {
      bool operator()(Utilisation* a, Utilisation* b)
      {
         return (*a).G_date() > (*b).G_date();
      }
   };

   lst.sort(comp());

   return;
}

// ###################################################
// Trier la liste par nom de l'�tablissement, croissante
// ###################################################
void Trieur::parEtablissementAsc(list<Utilisation*>& lst)
{
   struct comp
   {
      bool operator()(Utilisation* a, Utilisation* b)
      {
         return (*a).G_etablissement() < (*b).G_etablissement();
      }
   };

   lst.sort(comp());

   return;
}

// ###################################################
// Trier la liste par nom de l'�tablissement, d�croissante
// ###################################################
void Trieur::parEtablissementDesc(list<Utilisation*>& lst)
{
   struct comp
   {
      bool operator()(Utilisation* a, Utilisation* b)
      {
         return (*a).G_etablissement() > (*b).G_etablissement();
      }
   };

   lst.sort(comp());

   return;
}
