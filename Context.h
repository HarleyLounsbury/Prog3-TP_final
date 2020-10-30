// Context.h
// Déclaration de class "Context"
// Contenant pour le programme: affichage, appels de fonctions.
// Auteur: Harley Lounsbury
// Date: 2019-12-16

class Context
{
private:

   // Menu principal.
   void ecranBienvenue();
   char menuPrincipal();

   // Section Citoyen.
   void traiterCitoyen();
   void chercherCitoyenNonIndexe(string NAS);
   void chercherCitoyenIndexe(string NAS);
   void vueCitoyen(Citoyen& cit);
   void afficherSommaireCitoyen(Citoyen& cit);
   char menuCitoyen();

   void vueProbleme(Citoyen& cit);
   char menuProbleme();
   void vueBlessure(Citoyen& cit);
   void vueMaladie(Citoyen& cit);
   void vueProblemeTous(Citoyen& cit);

   void vueRessource(Citoyen& cit);
   void enteteVueRessource(Citoyen& cit);
   char menuRessource();
   void vueRendezvous(Citoyen& cit);
   void vueHospitalisation(Citoyen& cit);
   void vueRessourceToutes(Citoyen& cit);


   // Section Professionnel de la santé.
   void traiterProfessionnel();
   bool validerCodePS(string codePS);
   void chercherProfessionnelNonIndexe(string codePS);
   void chercherProfessionnelIndexe(string codePS);
   void vueProfessionnel(ProfessionnelSante& pro);
   void enTeteProfessionnel(ProfessionnelSante& pro);
   char menuProfessionnel();

   void vuePatient(ProfessionnelSante& pro);
   char menuPatient();
   void enTeteListePatient(string nom);
   void afficherListePatient(ProfessionnelSante& pro);
   void vuePatientBrut(ProfessionnelSante& pro);
   void vuePatientNaissance(ProfessionnelSante& pro);
   void vuePatientNaissanceDec(ProfessionnelSante& pro);
   void vuePatientNAS(ProfessionnelSante& pro);
   void vuePatientNASDec(ProfessionnelSante& pro);
   void vuePatientNom(ProfessionnelSante& pro);
   void vuePatientNomDec(ProfessionnelSante& pro);

   void vueIntervention(ProfessionnelSante& pro);
   char menuIntervention();
   void enTeteListeInterventions(string nom);
   void afficherListeInterventions(ProfessionnelSante& pro);
   void vueInterventionDate(ProfessionnelSante& pro);
   void vueInterventionDateDesc(ProfessionnelSante& pro);
   void vueInterventionEtablissement(ProfessionnelSante& pro);
   void vueInterventionEtablissementDesc(ProfessionnelSante& pro);
   void vueInterventionBrut(ProfessionnelSante& pro);

public:
   void Init();
};