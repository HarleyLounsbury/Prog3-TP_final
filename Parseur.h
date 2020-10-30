// Parseur.h
// D�claration de type param�tr� pour s�parer des informations, cr�er des objets. 
//
// Auteur: Harley Lounsbury
// Date: 2019-11-01

// ##############################
// Structure de la classe.
// ##############################
template <class T>
class Parseur
{
private:
	string separateur;

public:
	Parseur(string s);
	int CompteurChamp(string ligne);
	void Decouper(string lc, vector<string> &tabValeurs, int nbChamps);
	int ValiderMinLongeurChamps(int nbChamps, int tabLongueurs[], string tabValeurs[]);
	int ValiderMaxLongeurChamps(int nbChamps, int tabLongueurs[], string tabValeurs[]);
	T* Instancier(string valeurs[]);
};

// ##############################
// Constructeur
// ##############################
template <class T>
Parseur<T>::Parseur(string s)
{
	separateur = s;
}

// ##############################
// CompteurChamp(string ligne) - compte les champs, retourne ce nombre.
// ##############################
template <class T>
int Parseur<T>::CompteurChamp(string ligne)
{
	int compteur = 0;
	for (unsigned int i = 0; i < ligne.length(); i++)
	{
		if (ligne[i] == separateur[0])
			compteur++;
	}
	return compteur;
}

// ##############################
// Decouper(string lc, string tabValeurs[]) - d�coupe la ligne en question et stocker les valeurs dans un tableau de string.
// ##############################
template <class T>
void Parseur<T>::Decouper(string lc, vector<string> &tabValeurs, int nbChamps)
{
	int position;
	for (int i = 0; i < nbChamps; i++)
	{
		position = lc.find(separateur);
		if (position != -1)
		{
			tabValeurs.emplace_back(lc.substr(0, position));
			lc = lc.substr(position + 1);
		}
      else
      {
         position = lc.find("\n");
         tabValeurs.emplace_back(lc.substr(0, position));
      }
	}
	return;
}

// ##############################
// Instancier(string valeurs[]) - Instancier un nouveau objet dynamiquement.
// ##############################
template <class T>
T* Parseur<T>::Instancier(string valeurs[])
{
	return new T(valeurs);
}

// ##############################
// ValiderMinLongeurChamps(int nbChamps, int tabLongueurs[], string tabValeurs[]) 
// Param�tres: le nombre de champs, un tableau de longueurs corr�spondantes, et les valeurs.
// ##############################
template <class T>
int Parseur<T>::ValiderMinLongeurChamps(int nbChamps, int tabLongueurs[], string tabValeurs[])
{
	// Comparer chaque champs � son minimum longueur, retourne l'indice du champ trop petit.
	// Valeur de retour de -1 indique que toutes les champs respecte les maximums.
	for (int i = 0; i < nbChamps; i++)
	{
		if (tabValeurs[i].length() < tabLongueurs[i])
			return i;
	}
	return -1;
}

// ##############################
// ValiderMaxLongeurChamps(int nbChamps, int tabLongueurs[], string tabValeurs[])
// Param�tres: le nombre de champs, un tableau de longueurs corr�spondantes, et les valeurs.
// ##############################
template <class T>
int Parseur<T>::ValiderMaxLongeurChamps(int nbChamps, int tabLongueurs[], string tabValeurs[])
{
	// Comparer chaque champs � son maximum longueur, retourne l'indice du champ trop long.
	// Valeur de retour de -1 indique que toutes les champs respecte les maximums.
	for (int i = 0; i < nbChamps; i++)
	{
		if (tabValeurs[i].length() > tabLongueurs[i])
			return i;
	}
	return -1;
}