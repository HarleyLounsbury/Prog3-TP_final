// Trieur.h
// Déclaration de class "Trieur"
// Méchanisms pour trier des informations dans des listes, selon un critère.
// Auteur: Harley Lounsbury
// Date: 2019-12-16

class Trieur
{
public:
   // Patients
   void parNaissanceAsc(list<Citoyen*>& lst);
   void parNaissanceDesc(list<Citoyen*>& lst);
   void parNASAsc(list<Citoyen*>& lst);
   void parNASDesc(list<Citoyen*>& lst);
   void parNomAsc(list<Citoyen*>& lst);
   void parNomDesc(list<Citoyen*>& lst);

   // Interventions
   void parDateAsc(list<Utilisation*>& lst);
   void parDateDesc(list<Utilisation*>& lst);
   void parEtablissementAsc(list<Utilisation*>& lst);
   void parEtablissementDesc(list<Utilisation*>& lst);
};