// Biblio.h
// Dépôt d'inclusions pour le programme "Regard Santé"
// Auteur: Harley Lounsbury
// Date: 2019-12-16


#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "windows.h"
#include <sstream>

#include <algorithm>
#include <iterator>
#include <vector>
#include <list>

using namespace std;

#include "Parseur.h" 
#include "Index.h"

#include "Utilisation.h"
#include "Rendezvous.h"
#include "Hospitalisation.h"

#include "Probleme.h"
#include "Blessure.h"
#include "Maladie.h"

#include "UsineProbleme.h"
#include "UsineUtilisation.h"

#include "Citoyen.h"
#include "ProfessionnelSante.h"

#include "UsineCitoyen.h"

#include "Context.h"
#include "Trieur.h"

const string FICHIER_POPULATION = "d:\\utopia\\donnees\\population.txt";
const string FICHIER_PROBLEMES = "d:\\utopia\\donnees\\problemes.txt";
const string FICHIER_UTILISATIONS = "d:\\utopia\\donnees\\utilisations.txt";

const string FICHIER_INDEX_CITOYENS = "d:\\utopia\\index\\indexCitoyens.txt";
const string FICHIER_INDEX_PROFESSIONNELS = "d:\\utopia\\index\\indexProfessionnels.txt";
const string FICHIER_INDEX_PROBLEMES = "d:\\utopia\\index\\indexProblemes.txt";
const string FICHIER_INDEX_UTILISATIONS = "d:\\utopia\\index\\indexUtilisations.txt";
const string FICHIER_INDEX_PATIENTS = "d:\\utopia\\index\\indexPatients.txt";
const string FICHIER_INDEX_INTERVENTIONS = "d:\\utopia\\index\\indexInterventions.txt";

static UsineProbleme UP;
static UsineUtilisation UU;
static UsineCitoyen UC;
static Index Indexeur;

// 
const int CODE_PS_MAX = 6;
const int CODE_PS_MIN = 3;
// codes connu
const vector<string> CODES_PS = { "PHY", "MG", "N", "ERG", "RO" };