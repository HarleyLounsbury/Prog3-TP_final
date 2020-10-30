// UsineCitoyen.h
// Déclaration de class "UsineCitoyen"
// Abstraction de l'allocation dynamique.
// Auteur: Harley Lounsbury
// Date: 2019-12-16


class UsineCitoyen
{
public:
   Citoyen* CreerCitoyen(vector<string> valeurs, bool estIndexe);
   Citoyen* CreerPatient(vector<string> valeurs, bool estIndexe);
};