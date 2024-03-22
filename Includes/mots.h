#ifndef _DICO_CONST
#define _DICO_CONST
// Structure pour stocker le dictionnaire des mots
// Elle contient un tableau dynamique de mots et le compteur du nombre de mots
struct Dictionnaire
{
    // Tableau dynamique de mots
    char **mots;
    // Compteur du nombre de mots
    int nbMots;
};

// Structure pour le résultat d'un ligne contenant le nombre de lettres bien
// placées et le nombre de lettre mal placées
struct ResultatLigne
{
    // Nombre de lettres bien placées
    int bienPlaces;
    // Nombre de lettres mal placées
    int malPlaces;
};
#endif

// Déclaration des fonctions du module
bool VerifierMot(char *motAVerifier);
struct Dictionnaire *LireDictionnaire(char *nomDeFichier, struct Dico_Message *messageDeRetour);
void EffacerDictionnaire(struct Dictionnaire *dictionnaire);
bool ComparerMots(char *solution, char *motPlace, struct ResultatLigne *resultat);