// Index.h
// Déclaration de class "Index"
// Méchanism pour indexer des informations.
// Étant donné qu dire'un objet Index n'a pas d'état (c'est à, il ne contient pas d'attribut modifiable), la classe fonctionne bien pour encapsulation.
// Fonctionnement: variable static global
// Auteur: Harley Lounsbury
// Date: 2019-12-16


class Index
{
private:
   string fausseDate = "1900-01-01 00:00:00:000";

   string obtenirDateFichier(string nomFichier);
   bool indexationEstAJour(const string nomFichierInfo, const string nomFichierIndex);
   void effacerIndexationErrone();

public:
   bool IndexationEstValide();
   int chercherNombreDeLignesFichier(string nomFichier);

   // Pour citoyens.
   bool estIndexeCitoyen(string NAS);
   void IndexerCitoyen(string NAS, int position);
   int retournerIndexCitoyen(string NAS);

   // Pour professionnels de la santé.
   bool estIndexeProfessionnel(string codePS);
   void IndexerProfessionnel(string codePS, int position);
   int retournerIndexProfessionnel(string codePS);

   void IndexerProblemes(string NAS, vector<int> positions);
   void IndexerUtilisations(string NAS, vector<int> positions);
   
   void IndexerPatients(string codePS, vector<int> positions);
   void IndexerInterventions(string codePS, vector<int> positions);
};