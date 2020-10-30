// ProfessionnelSante.h
// Déclaration de class "ProfessionnelSante"
// Auteur: Harley Lounsbury
// Date: 2019-12-16


class ProfessionnelSante : public Citoyen
{
private:
   string codePS;
   string titre;

   list<Citoyen*> lstPatients;
   list<Utilisation*> lstInterventions;

   vector<string> NASPatients;
   vector<int> intNASPatients;
   bool NASExiste(string NAS);

   void importerInterventionsNonIndexes();
   void importerPatientsNonIndexes();

   void importerPatientsIndexes();
   void importerInterventionsIndexes();


public:
   ProfessionnelSante(vector<string> valeurs, bool estIndexe);
   ~ProfessionnelSante();

   string G_titre();
   list<Citoyen*>* G_lstPatients();
   list<Utilisation*>* G_lstInterventions();

   int CompteInterventionsPourPatient(int NAS);
};